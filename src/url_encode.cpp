#include "url_encode.hpp"

void urlencode_string(String &str)
{
    str.replace("%", "%25");
    str.replace(" ", "%20");
    str.replace("!", "%21");
    str.replace("\"", "%22");
    str.replace("$", "%24");
    str.replace("&", "%26");
    str.replace("'", "%27");
    str.replace("(", "%28");
    str.replace(")", "%29");
    str.replace("*", "%2A");
    str.replace("+", "%2B");
    str.replace(",", "%2C");
    str.replace("-", "%2D");
    str.replace(".", "%2E");
    str.replace("/", "%2F");
    str.replace(":", "%3A");
    str.replace(";", "%3B");
    str.replace("=", "%3D");
    str.replace("?", "%3F");
    str.replace("@", "%40");
    str.replace("[", "%5B");
    str.replace("\\", "%5C");
    str.replace("]", "%5D");
    str.replace("^", "%5E");
    str.replace("_", "%5F");

    str.replace("linebreak", "%0A");
}