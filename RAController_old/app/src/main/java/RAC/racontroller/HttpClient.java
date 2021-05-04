package RAC.racontroller;

import okhttp3.OkHttpClient;

class HttpClient {
    private static final HttpClient httpclient = new HttpClient();
    private OkHttpClient client;
    private String IP;

    private HttpClient() {}

    static HttpClient getInstance() {
        return httpclient;
    }

    OkHttpClient getClient() {
        return client;
    }

    void setClient(OkHttpClient client) {
        this.client = client;
    }

    String getIP() {
        return IP;
    }

    void setIP(String IP) {
        this.IP = IP;
    }
}
