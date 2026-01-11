#!/bin/bash

# ==================== 配置参数 ====================
RECORD_ROOT="$HOME/Public/recordings"       # 录音文件存储根目录（可自定义）
RECORD_HOUR=24                       # 总录音时长（小时）
RECORD_INTERVAL=3600                 # 单次录音时长（秒，3600=1小时）
RETENTION_DAYS=$((6 * 30))             # 录音保留天数（6个月≈180天）

# ==================== 初始化环境 ====================
# 创建根目录（若不存在）
mkdir -p "$RECORD_ROOT"

# ==================== 定义核心函数 ====================
# 功能：清理超过保留天数的旧录音
clean_old_recordings() {
    echo "[$(date +'%Y-%m-%d %H:%M:%S')] 开始清理超过 ${RETENTION_DAYS} 天的录音..." >> $RECORD_ROOT/recordings.log
    # 使用 find 命令查找并删除旧文件（-mtime +180 表示180天前修改的文件）
    find "$RECORD_ROOT" -type f -name "*.wav" -mtime "+${RETENTION_DAYS}" -delete -print
    echo "[$(date +'%Y-%m-%d %H:%M:%S')] 清理完成。" >> $RECORD_ROOT/recordings.log
}

# 功能：执行单次录音并保存到日期文件夹
single_record() {
    local current_time=$(date +%Y%m%d%H%M)  # 当前时间（精确到分钟）
    local current_date=$(date +%Y/%m/%d)    # 当前日期（格式：年/月/日）
    local save_path="$RECORD_ROOT/$current_date/recording_${current_time}.wav"  # 完整保存路径
    
    # 创建日期文件夹（如：2024/05/20）
    mkdir -p "$(dirname "$save_path")"
    
    echo "[$(date +'%Y-%m-%d %H:%M:%S')] 开始录制：$save_path" >> $RECORD_ROOT/recordings.log
    # 执行录音命令（-d 指定单次录音时长，-f cd 高音质，-t wav 格式）
    arecord -d "$RECORD_INTERVAL" -f cd -t wav "$save_path"
    
    # 检查录音是否成功
    if [ $? -eq 0 ]; then
        echo "[$(date +'%Y-%m-%d %H:%M:%S')] 录制完成，文件大小：$(du -h "$save_path" | awk '{print $1}')" >> $RECORD_ROOT/recordings.log
    else
        echo "[$(date +'%Y-%m-%d %H:%M:%S')] 录制中断，文件大小：$(du -h "$save_path" | awk '{print $1}')" >> $RECORD_ROOT/recordings.log
        return 1  # 返回错误码
    fi
}

# ==================== 主流程 ====================
echo "===== 自动录音脚本启动 =====" >> $RECORD_ROOT/recordings.log
echo "录音根目录：$RECORD_ROOT" >> $RECORD_ROOT/recordings.log
echo "总录音时长：${RECORD_HOUR} 小时" >> $RECORD_ROOT/recordings.log
echo "单次录音时长：$((RECORD_INTERVAL/60)) 分钟" >> $RECORD_ROOT/recordings.log
echo "录音保留天数：${RETENTION_DAYS} 天" >> $RECORD_ROOT/recordings.log
echo "==============================" >> $RECORD_ROOT/recordings.log

# 先清理一次旧文件（避免历史文件堆积）
clean_old_recordings

# 计算总录音秒数（用于循环控制）
total_seconds=$((RECORD_HOUR * 3600))
start_time=$(date +%s)       # 记录启动时间戳
end_time=$((start_time + total_seconds))  # 计算结束时间戳

# 循环录音直到达到总时长
while [ $(date +%s) -lt $end_time ]; do
    # 执行单次录音
    single_record
    
    # 计算剩余时间并等待（避免因录音失败导致超时）
    current_elapsed=$(( $(date +%s) - start_time ))
    remaining_time=$(( end_time - $(date +%s) ))
    
    if [ $remaining_time -gt 0 ]; then
        echo "[$(date +'%Y-%m-%d %H:%M:%S')] 剩余时间：$((remaining_time/3600)) 小时 $(( (remaining_time%3600)/60 )) 分钟" >> $RECORD_ROOT/recordings.log
        sleep $RECORD_INTERVAL  # 等待单次录音间隔（1小时）
    else
        echo "[$(date +'%Y-%m-%d %H:%M:%S')] 总录音时间已到，退出循环。" >> $RECORD_ROOT/recordings.log
        break
    fi
done

# 最后清理一次旧文件（确保任务结束后无冗余）
clean_old_recordings

echo "===== 自动录音脚本结束 ===== \n" >> $RECORD_ROOT/recordings.log
