
//#include <video.h>
//#include <print>
//#include <cstdlib>

////todo add logger spdlog

//int handle_error(std::expected<void, xstream::VideoErrorInfo> & ret){
//  std::println("{}", ret.error().message);
//  return EXIT_FAILURE;
//}

//int main(int argc,char ** argv){
//  if (argc < 2){
//    std::println("Usage: {} <path_2_video>.mp4",argv[0]);
//    return EXIT_FAILURE;
//  }
//  xstream::Stream<xstream::Video> video_stream;
//  //init player's pipeline
//  auto ret = video_stream.init(argv[1],argc,argv);
//  if (!ret) return handle_error(ret);

//  ret=video_stream.start();
//  if (!ret) return handle_error(ret);
//  for(;;){}
//  return 0;
//}
#include <gst/gst.h>
#include <iostream>

int main(int argc, char *argv[])
{
    gst_init(&argc, &argv);

    GstElement *pipeline = gst_element_factory_make("playbin", "player");

    if (!pipeline) {
        std::cerr << "Failed to create playbin\n";
        return 1;
    }

    // Replace with your file path
    g_object_set(
        pipeline,
        "uri",
        "file:///home/cxx-core/rc/sintel_trailer-H265bq.mp4",
        nullptr);

    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    GstBus *bus = gst_element_get_bus(pipeline);
    GstMessage *msg = gst_bus_timed_pop_filtered(
        bus,
        GST_CLOCK_TIME_NONE,
        static_cast<GstMessageType>(
            GST_MESSAGE_ERROR |
            GST_MESSAGE_EOS));

    if (msg != nullptr) {
        switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_ERROR:
        {
            GError *err;
            gchar *debug;

            gst_message_parse_error(msg, &err, &debug);

            std::cerr << "Error: " << err->message << '\n';

            g_error_free(err);
            g_free(debug);
            break;
        }
        case GST_MESSAGE_EOS:
            std::cout << "Playback finished\n";
            break;
        default:
            break;
        }

        gst_message_unref(msg);
    }

    gst_object_unref(bus);

    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);

    return 0;
}
