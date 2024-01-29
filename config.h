/* This is an opinionated 'config.h': modify it directly or run `cp config.def.h config.h`. */
/* 'config.def.h' is the same as in the original slstatus repository except updated comments. */

#include <stdlib.h>
#include "slstatus.h"

/* interval between updates (in ms) */
const unsigned int interval = 2 * 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 128

/*
 * function            description                     argument (example)
 *
 * battery_perc        battery percentage              battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_remaining   battery remaining HH:MM         battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * battery_state       battery charging state          battery name (BAT0)
 *                                                     NULL on OpenBSD/FreeBSD
 * cat                 read arbitrary file             path
 * cpu_freq            cpu frequency in MHz            NULL
 * cpu_perc            cpu usage in percent            NULL
 * datetime            date and time                   format string (%F %T)
 * disk_free           free disk space in GB           mountpoint path (/)
 * disk_perc           disk usage in percent           mountpoint path (/)
 * disk_total          total disk space in GB          mountpoint path (/)
 * disk_used           used disk space in GB           mountpoint path (/)
 * entropy             available entropy               NULL
 * gid                 GID of current user             NULL
 * hostname            hostname                        NULL
 * ipv4                IPv4 address                    interface name (eth0)
 * ipv6                IPv6 address                    interface name (eth0)
 * kernel_release      `uname -r`                      NULL
 * keyboard_indicators caps/num lock indicators        format string (c?n?)
 *                                                     see keyboard_indicators.c
 * keymap              layout (variant) of current     NULL
 *                     keymap
 * keymap_uppercase    layout (variant) of current     NULL
 *                     keymap, uppercased
 * load_avg            load average                    NULL
 * netspeed_rx         receive network speed           interface name (wlan0)
 * netspeed_tx         transfer network speed          interface name (wlan0)
 * num_files           number of files in a directory  path
 *                                                     (/home/foo/Inbox/cur)
 * ram_free            free memory in GB               NULL
 * ram_perc            memory usage in percent         NULL
 * ram_total           total memory size in GB         NULL
 * ram_used            used memory in GB               NULL
 * run_command         custom shell command            command (echo foo)
 * swap_free           free swap in GB                 NULL
 * swap_perc           swap usage in percent           NULL
 * swap_total          total swap size in GB           NULL
 * swap_used           used swap in GB                 NULL
 * temp                temperature in degree celsius   sensor file
 *                                                     (/sys/class/thermal/...)
 *                                                     NULL on OpenBSD
 *                                                     thermal zone on FreeBSD
 *                                                     (tz0, tz1, etc.)
 * uid                 UID of current user             NULL
 * uptime              system uptime                   NULL
 * username            username of current user        NULL
 * vol_perc            PulseAudio/PipeWire volume in   sink ID (@DEFAULT_SINK@, 1, etc)
 *                     percent (can be > 100)
 * vol_mute            Audio sink mute status          sink ID (@DEFAULT_SINK@, 1, etc)
 *                     as MUT or VOL
 * wifi_essid          WiFi ESSID                      interface name (wlan0)
 * wifi_perc           WiFi signal in percent          interface name (wlan0)
 */

/* Example: "US | MUT 40% | RAM 12% | CPU 0% | BAT 82% | Mon Jan 29 04:34 PM" */
/* Each line is processed like `printf(args[i].fmt, args[i].func(args[i].args))` */
static const struct arg args[] = {
	/* function   format   argument */
  { keymap_uppercase, "%s | " },
  /* To get audio sink IDs/names, run `wpctl status`, `pactl list sinks`, or an analog */
  { vol_mute, "%s ", "@DEFAULT_SINK@" },
  { vol_perc, "%s%% | ", "@DEFAULT_SINK@" },
  { ram_perc, "RAM %s%% | ", NULL },
  { cpu_perc, "CPU %s%% | ", NULL },
  { battery_perc, "BAT %s%% | ", "BAT0" },
	{ datetime, "%s", "%a %b %d %I:%M %p" },
};
