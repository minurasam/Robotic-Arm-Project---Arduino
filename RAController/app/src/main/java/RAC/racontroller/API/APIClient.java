package RAC.racontroller.API;

import java.util.concurrent.ExecutionException;

import okhttp3.OkHttpClient;

public class APIClient {
    private static final APIClient APICLIENT = new APIClient();

    private OkHttpClient client;
    private String IP;

    private APIClient() {}

    public static APIClient getInstance() {
        return APICLIENT;
    }

    public String getIP() {
        return IP;
    }

    public void setIP(String IP) {
        this.IP = IP;
    }

    OkHttpClient getClient() {
        return client;
    }

    void setClient(OkHttpClient client) {
        this.client = client;
    }

    public static boolean login(String address, String username, String password) {
            try {
                LoginAsync loginAsync = new LoginAsync();
                return loginAsync.execute(new LoginDetails(address, username, password)).get();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (ExecutionException e) {
                e.printStackTrace();
            }
            return false;
    }

    public static boolean postData(String name, String value){
        try {
            PostAsync postAsync = new PostAsync();
            return postAsync.execute(new PostDataDetails(name, value)).get();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (ExecutionException e) {
            e.printStackTrace();
        }
        return false;
    }
}