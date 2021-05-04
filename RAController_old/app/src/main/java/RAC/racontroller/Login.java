package RAC.racontroller;

import android.os.AsyncTask;

import com.burgstaller.okhttp.AuthenticationCacheInterceptor;
import com.burgstaller.okhttp.CachingAuthenticatorDecorator;
import com.burgstaller.okhttp.digest.CachingAuthenticator;
import com.burgstaller.okhttp.digest.Credentials;
import com.burgstaller.okhttp.digest.DigestAuthenticator;

import java.io.IOException;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

import okhttp3.OkHttpClient;
import okhttp3.Request;

public class Login extends AsyncTask<LoginDetails, Void, Boolean> {

    protected Boolean doInBackground(LoginDetails... loginDetails) {
        final DigestAuthenticator authenticator = new DigestAuthenticator(new Credentials(loginDetails[0].getUsername(), loginDetails[0].getPassword()));

        final Map<String, CachingAuthenticator> authCache = new ConcurrentHashMap<>();
        OkHttpClient client = new OkHttpClient.Builder()
                .authenticator(new CachingAuthenticatorDecorator(authenticator, authCache))
                .addInterceptor(new AuthenticationCacheInterceptor(authCache))
                .build();

        Request request = new Request.Builder().url(loginDetails[0].getAddress()).get().build();

        try {
            if(client.newCall(request).execute().isSuccessful()){
                HttpClient.getInstance().setClient(client);
                return true;
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }
}

class LoginDetails {
    private String address;
    private String username;
    private String password;

    LoginDetails(String address, String username, String password) {
        this.address = address;
        this.username = username;
        this.password = password;
    }

    String getAddress() {
        return address;
    }

    String getUsername() {
        return username;
    }

    String getPassword() {
        return password;
    }
}