#include <stdio.h>
#include <stdlib.h>

#include <pulse/pulseaudio.h>

static char vol_str[8] = {'\0'};
static int vol_muted = 0;

static pa_mainloop *mainloop = NULL;
static int data_ready = 0;

void context_state_cb(pa_context *c, void *userdata);
void sink_info_cb(pa_context *c, const pa_sink_info *i, int eol, void *userdata);

void prepare_data(const char *card) {
  data_ready = 0;

  mainloop = pa_mainloop_new();
  pa_mainloop_api *mainloop_api = pa_mainloop_get_api(mainloop);
  pa_context *context = pa_context_new(mainloop_api, "get_sink_information");

  pa_context_set_state_callback(context, context_state_cb, (void *)card);
  pa_context_connect(context, NULL, PA_CONTEXT_NOFLAGS, NULL);

  while (!data_ready) {
    pa_mainloop_iterate(mainloop, 1, NULL);
  }

  pa_context_disconnect(context);
  pa_context_unref(context);
  pa_mainloop_free(mainloop);
}

const char *vol_perc(const char *card) {
  prepare_data(card);
  return vol_str;
}

const char *vol_mute(const char *card) {
  prepare_data(card);
  static char key[16] = {'\0'};
  snprintf(key, sizeof(key), "%s", vol_muted ? "MUT" : "VOL");
  return key;
}

void context_state_cb(pa_context *c, void *userdata) {
  const char *card_name = userdata;
  switch (pa_context_get_state(c)) {
    case PA_CONTEXT_READY:
      pa_context_get_sink_info_by_name(c, card_name, sink_info_cb, NULL);
      break;
    case PA_CONTEXT_FAILED:
    case PA_CONTEXT_TERMINATED:
      data_ready = 1;
      break;
    default:
      break;
  }
}

void sink_info_cb(pa_context *c, const pa_sink_info *i, int eol, void *userdata) {
  if (eol > 0) {
    data_ready = 1;
    return;
  }

  unsigned volume_percent = (unsigned)(100 * pa_cvolume_avg(&(i->volume)) / PA_VOLUME_NORM);
  snprintf(vol_str, sizeof(vol_str), "%u", volume_percent);

  vol_muted = i->mute;

  data_ready = 1;
}
