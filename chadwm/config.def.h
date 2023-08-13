/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* 外观 */
static const unsigned int borderpx  = 0;        /* 窗口的边框像素 */
static const unsigned int default_border = 0;   /* 通过快捷键动态调整边框大小后切会默认边框大小 */
static const unsigned int snap      = 32;       /* 快照像素 */
static const unsigned int gappih    = 10;       /* 窗口之间的水平内部间隙 */
static const unsigned int gappiv    = 10;       /* 垂直窗口之间的内部间隙 */
static const unsigned int gappoh    = 10;       /* 窗口和屏幕边缘之间的水平外部间隙 */
static const unsigned int gappov    = 10;       /* 垂直窗口和屏幕边缘之间的外部间隙 */
static const int smartgaps          = 0;        /* 1: 表示一个窗口时没有外部间隙 */
static const unsigned int systraypinning = 0;   /* 0: sloppy 系统托盘跟随选定的显示器, >0: 固定系统托盘并监控 X11 */
static const unsigned int systrayspacing = 2;   /* 系统托盘间隙 */
static const int systraypinningfailfirst = 1;   /* 1: 如果固定失败，在第一台显示器上显示系统托盘,否则:在最后一个显示器上显示系统托盘 */
static const int showsystray        = 1;        /* 0 表示没有系统托盘 */
static const int showbar            = 1;        /* 0 表示没有 barner */
static const int showtab            = showtab_auto;
static const int toptab             = 1;        /* 0 表示顶栏 */
static const int topbar             = 1;        /* 0 表示底栏 */
static const int horizpadbar        = 5;
static const int vertpadbar         = 11;
static const int vertpadtab         = 35;
static const int horizpadtabi       = 15;
static const int horizpadtabo       = 15;
static const int scalepreview       = 4;
static const int tag_preview        = 1;        /* 状态栏窗口缩略图 1 启用, 0 关闭 */
static const int colorfultag        = 1;        /* 0 表示对选定的非空标签使用方案 */

#define ICONSIZE 19   /* 图标大小 */
#define ICONSPACING 8 /* 图标和标题之间的空白 */

// 提示：yay -S nerd-fonts-jetbrains-mono nerd-fonts-ubuntu-mono ttf-material-design-icons-desktop-git
static const char *fonts[]          = {"Iosevka:style:medium:size=11" ,"JetBrainsMono Nerd Font:style:medium:size=11",
                                        "Material Design Icons Desktop:size=11", "Ubuntu Nerd Font Mono:size=11" };

// 主题
#include "themes/onedark.h"

static const char *colors[][3]      = {
    /*                     字色     背景色  边框 */
    [SchemeNorm]       = { gray3,   black,  gray2 },
    [SchemeSel]        = { gray4,   blue,   blue  },
    [SchemeTitle]      = { white,   black,  black }, // 活动窗口的标题
    [TabSel]           = { blue,    gray2,  black },
    [TabNorm]          = { gray3,   black,  black },
    [SchemeTag]        = { gray3,   black,  black },
    [SchemeTag1]       = { green,   black,  black },
    [SchemeTag2]       = { blue,    black,  black },
    [SchemeTag3]       = { orange,  black,  black },
    [SchemeTag4]       = { red,     black,  black },
    [SchemeTag5]       = { green,   black,  black },
    [SchemeLayout]     = { pink,    black,  black },
    [SchemeBtnPrev]    = { green,   black,  black },
    [SchemeBtnNext]    = { yellow,  black,  black },
    [SchemeBtnClose]   = { red,     black,  black },
};

/* tty 1~5 :图标来自 https://www.nerdfonts.com/cheat-sheet */
static char *tags[] = {"", "", "﬏", "", "", "", ""};

static const char* eww[] = { "eww", "open" , "eww", NULL };

static const Launcher launchers[] = {
    /* 命令     要显示的名称 */
    { eww,         "" },
};

static const int tagschemes[] = {
    SchemeTag1, SchemeTag2, SchemeTag3, SchemeTag4, SchemeTag2, SchemeTag4, SchemeTag5
};

static const unsigned int ulinepad      = 5; /* 下滑线和标签之间的水平填充 */
static const unsigned int ulinestroke   = 2; /* 下划线的厚度和高度 */
static const unsigned int ulinevoffset  = 0; /* 这条线应该出现在条形底部上方多远 */
static const int ulineall               = 0; /* 1 表示在所有标签上显示下划线，0 仅用于活动标签 */

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     iscentered   isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            0,           1,           -1 },
    { "Firefox",  NULL,       NULL,       1 << 8,       0,           0,           -1 },
    { "eww",      NULL,       NULL,       0,            0,           1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* 主区域元素大小 [0.05..0.95] */
static const int nmaster     = 1;    /* 主用户数 */
static const int resizehints = 0;    /* 1 表示在平铺调整中提供大小提示 */
static const int lockfullscreen = 1; /* 1 将强制专注于全屏窗口 */

#define FORCE_VSPLIT 1  /* 窄网格布局: 强制两个客户端始终垂直分裂 */
#include "functions.h"


static const Layout layouts[] = {
    /* 象征       排列功能 */
    { "",        tile },    /* 第一个条目是默认的 */
    { "",        monocle },
    { "",        spiral },
    { "[\\]",     dwindle },
    { "H[]",      deck },
    { "TTT",      bstack },
    { "===",      bstackhoriz },
    { "HHH",      grid },
    { "###",      nrowgrid },
    { "---",      horizgrid },
    { "",        gaplessgrid },
    { "|M|",      centeredmaster },
    { ">M>",      centeredfloatingmaster },
    { "",        NULL },    /* 没有布局功能意味着是浮动的 */
    { NULL,       NULL },
};

/* 关键定义 */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* 以 dwm-5.0 之前的方式生成 shell 命令的助手 */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* 所有命令 */

static Key keys[] = {
    /* 修饰符                          key         function        argument */

    // 亮度和音频（补充：pacman -S pamixer acpilight/xorg-xbacklight & sudo gpasswd video -a $USER） 
    {0,                     XF86XK_AudioMute,       spawn,          SHCMD("pamixer -t")},
    {0,              XF86XK_AudioRaiseVolume,       spawn,          SHCMD("pamixer -i 5")},
    {0,              XF86XK_AudioLowerVolume,       spawn,          SHCMD("pamixer -d 5")},
    {0,              XF86XK_MonBrightnessDown,      spawn,          SHCMD("xbacklight -dec 5")},
    {0,              XF86XK_MonBrightnessUp,        spawn,          SHCMD("xbacklight -inc 5")},

    // 「常用」自由截图到剪贴板[Ctrl+Win+A][Win+U]（补充：pacman -S maim xclip）
    { MODKEY,                           XK_u,       spawn,
      SHCMD("maim | xclip -selection clipboard -t image/png")},
    { ControlMask|MODKEY,               XK_a,       spawn,
      SHCMD("maim --select | xclip -selection clipboard -t image/png")},

    // 使用 rofi 运行 drun 应用程序启动器[Win+C]（补充：pacman -S rofi）
    { MODKEY,                           XK_c,       spawn,          
      SHCMD("rofi -show drun -theme $HOME/.config/chadwm/rofi/themes/nord.rasi") },
    // 打开一个新终端[Win+回车],不想用 st 终端可以换别的，名字改下
    { MODKEY,                           XK_Return,  spawn,            SHCMD("st")},

    // 切换东西
    // 隐藏顶部 barner 再按一次重新显示[Win+B]
    { MODKEY,                           XK_b,       togglebar,      {0} },
    // 取消顶部 barner 和下方主窗口之间的间隙，再按还原[Win+Ctrl+T]
    { MODKEY|ControlMask,               XK_t,       togglegaps,     {0} },
    // 取消两个窗口中间的缝隙，再按还原[Win+Shift+空格] 
    { MODKEY|ShiftMask,                 XK_space,   togglefloating, {0} },
    // 「常用」活动窗口全屏显示，再按还原 [Win+F]（记忆：左手边有凸点的按键）
    { MODKEY,                           XK_f,       togglefullscr,  {0} },
     
    // 未知[Win+Ctrl+W]
    { MODKEY|ControlMask,               XK_w,       tabmode,        { -1 } },
    // 「常用」光标窗口间顺时针切换[Win+J]（记忆：右手边有凸点的按键） 
    { MODKEY,                           XK_j,       focusstack,     {.i = +1 } },
    // 「常用」光标窗口间逆时针切换[Win+K] 
    { MODKEY,                           XK_k,       focusstack,     {.i = -1 } },
    // 窗口上下分栏布局[Win+I]
    { MODKEY,                           XK_i,       incnmaster,     {.i = +1 } },
    // 窗口左右分栏布局[Win+D]
    { MODKEY,                           XK_d,       incnmaster,     {.i = -1 } },

    // 改变 mfact 和 cfact 大小
    // 右边窗口向左扩张[Win+H]
    { MODKEY,                           XK_h,       setmfact,       {.f = -0.05} },
    // 右边窗口向右边收缩[Win+L]
    { MODKEY,                           XK_l,       setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,                 XK_h,       setcfact,       {.f = +0.25} },
    { MODKEY|ShiftMask,                 XK_l,       setcfact,       {.f = -0.25} },
    { MODKEY|ShiftMask,                 XK_o,       setcfact,       {.f =  0.00} },


    // 窗口逆时针调换位置（常用）[Win+Shift+J]（补充：不加 Shift 是光标轮调，加 Shift 是窗口轮调）
    { MODKEY|ShiftMask,                 XK_j,       movestack,      {.i = +1 } },
    // 窗口顺时针调换位置[Win+Shift+K]
    { MODKEY|ShiftMask,                 XK_k,       movestack,      {.i = -1 } },
    { MODKEY|ShiftMask,                 XK_Return,  zoom,           {0} },
    // 当前工作区和新工作区两个（barner 左边 5 个 tty）之间来回切换（常用）[Win+Tab]
    { MODKEY,                           XK_Tab,     view,           {0} },

    // 整体窗口边距扩大[Win+Ctrl+I]
    { MODKEY|ControlMask,               XK_i,       incrgaps,       {.i = +1 } },
    // 整体窗口边距缩小[Win+Ctrl+D]
    { MODKEY|ControlMask,               XK_d,       incrgaps,       {.i = -1 } },

    // 窗口间内部间隙扩大[Win+Shift+I]
    { MODKEY|ShiftMask,                 XK_i,       incrigaps,      {.i = +1 } },
    // 窗口间内部间隙缩小[Win+Ctrl+Shift+I]
    { MODKEY|ControlMask|ShiftMask,     XK_i,       incrigaps,      {.i = -1 } },

    // 窗口间外部间隙扩大[Win+Ctrl+O]
    { MODKEY|ControlMask,               XK_o,       incrogaps,      {.i = +1 } },
    // 窗口间外部间隙扩大[Win+Ctrl+Shift+O]
    { MODKEY|ControlMask|ShiftMask,     XK_o,       incrogaps,      {.i = -1 } },

    // 内+外 hori, 垂直间隙（死都不会碰它的） 
    { MODKEY|ControlMask,               XK_6,       incrihgaps,     {.i = +1 } },
    { MODKEY|ControlMask|ShiftMask,     XK_6,       incrihgaps,     {.i = -1 } },
    { MODKEY|ControlMask,               XK_7,       incrivgaps,     {.i = +1 } },
    { MODKEY|ControlMask|ShiftMask,     XK_7,       incrivgaps,     {.i = -1 } },
    { MODKEY|ControlMask,               XK_8,       incrohgaps,     {.i = +1 } },
    { MODKEY|ControlMask|ShiftMask,     XK_8,       incrohgaps,     {.i = -1 } },
    { MODKEY|ControlMask,               XK_9,       incrovgaps,     {.i = +1 } },
    { MODKEY|ControlMask|ShiftMask,     XK_9,       incrovgaps,     {.i = -1 } },
    // 如果你不小心点了上面的，这里可以还原默认间隙（有用）[Win+Ctrl+Shift+D]
    { MODKEY|ControlMask|ShiftMask,     XK_d,       defaultgaps,    {0} },

    // [布局方案]
    // [Win+T] 左1 右3 T 字型（默认布局）
    { MODKEY,                           XK_t,       setlayout,      {.v = &layouts[0]} },
    // [Win+Shift+F] 主 1 且 barner 置底 
    { MODKEY|ShiftMask,                 XK_f,       setlayout,      {.v = &layouts[1]} },
    // [Win+G] 二分布局，裴波那契函数（推荐）
    { MODKEY,                           XK_g,       setlayout,      {.v = &layouts[2]} },
    // [Win+Ctrl+M] 四象限窗口分布布局（推荐）
    { MODKEY,                           XK_m,       setlayout,      {.v = &layouts[10]} },
    // [Win+Ctrl+T] 左上角小窗口置顶布局
    { MODKEY|ControlMask,               XK_t,       setlayout,      {.v = &layouts[13]} },
    // [Win+空格] 四象限窗口布局（推荐）
    { MODKEY,                           XK_space,   setlayout,      {0} },
    { MODKEY|ControlMask,               XK_comma,   cyclelayout,    {.i = -1 } },
    { MODKEY|ControlMask,               XK_period,  cyclelayout,    {.i = +1 } },
    { MODKEY,                           XK_0,       view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,                 XK_0,       tag,            {.ui = ~0 } },
    { MODKEY,                           XK_comma,   focusmon,       {.i = -1 } },
    { MODKEY,                           XK_period,  focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,                 XK_comma,   tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,                 XK_period,  tagmon,         {.i = +1 } },

    // 切换窗口边框大小
    // [Win+Shift+减] 减小所有窗口边框大小
    { MODKEY|ShiftMask,                 XK_minus,   setborderpx,    {.i = -1 } },
    // [Win+Shift+P] 扩大所有窗口边框大小
    { MODKEY|ShiftMask,                 XK_p,       setborderpx,    {.i = +1 } },
    // [Win+Shift+W] 还原窗口边框大小（有用）
    { MODKEY|ShiftMask,                 XK_w,       setborderpx,    {.i = default_border } },

    // [Win+Ctrl+Q] 退出 dwm 界面，回到 tty or dm （推荐）
    { MODKEY|ControlMask,               XK_q,       spawn,        SHCMD("killall bar.sh dwm") },

    // [Win+Q] 关闭当前活动窗口（推荐）
    { MODKEY,                           XK_q,       killclient,     {0} },

    // 重新打开当前活动窗口
    { MODKEY|ShiftMask,                 XK_r,       restart,           {0} },

    // 隐藏 & 重新显示窗口
    // [Win+E] 隐藏窗口
    { MODKEY,                           XK_e,       hidewin,        {0} },
    // [Wine+Shift+E] 重新显示
    { MODKEY|ShiftMask,                 XK_e,       restorewin,     {0} },

    TAGKEYS(                            XK_1,                       0)
    TAGKEYS(                            XK_2,                       1)
    TAGKEYS(                            XK_3,                       2)
    TAGKEYS(                            XK_4,                       3)
    TAGKEYS(                            XK_5,                       4)
    TAGKEYS(                            XK_6,                       5)
    TAGKEYS(                            XK_7,                       6)
    TAGKEYS(                            XK_8,                       7)
    TAGKEYS(                            XK_9,                       8)
};

/* 按钮定义 */
/* 点击可以是 ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin 或 ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          SHCMD("st") },

    /* 保持鼠标移动? */
    /* { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} }, */

    /* 鼠标选项，选择哪个更自然:
    *    0 - 平铺位置相对于鼠标光标
    *    1 - 平铺位置相对于窗口中心
    *    2 - 鼠标指针弯曲到窗口中心
    *
    * moveorplace 使用 movemouse 或 placemouse 取决于所选客户端的浮动状态。
    * 如果您想要单独控制这两个功能（即保留将平铺窗口移动到浮动位置的功能），请为两者设置不同的键绑定。
    */
    { ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkClientWin,         ControlMask,    Button1,        dragmfact,      {0} },
    { ClkClientWin,         ControlMask,    Button3,        dragcfact,      {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkTabBar,            0,              Button1,        focuswin,       {0} },
    { ClkTabBar,            0,              Button1,        focuswin,       {0} },
    { ClkTabPrev,           0,              Button1,        movestack,      { .i = -1 } },
    { ClkTabNext,           0,              Button1,        movestack,      { .i = +1 } },
    { ClkTabClose,          0,              Button1,        killclient,     {0} },
};
