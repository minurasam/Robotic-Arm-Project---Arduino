package RAC.racontroller;

import android.os.AsyncTask;
import android.util.Log;

import okhttp3.HttpUrl;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class PostData extends AsyncTask<PostDataDetails, Void, Boolean> {
    protected Boolean doInBackground(PostDataDetails... postDataDetails) {
        OkHttpClient client = HttpClient.getInstance().getClient();
        boolean result = true;

        for (PostDataDetails data : postDataDetails) {
            HttpUrl.Builder urlBuilder = HttpUrl.parse("http://" + HttpClient.getInstance().getIP() + "/api").newBuilder();
            urlBuilder.addQueryParameter(data.getName(), data.getValue());
            String url = urlBuilder.build().toString();

            Request request = new Request.Builder()
                    .url(url)
                    .build();

            try {
                Response response = client.newCall(request).execute();
                Log.d("debuginfo", response.message());
                Log.d("debuginfo", response.body().string());
            } catch (Exception e) {
                e.printStackTrace();
                result = false;
            }
        }
        return result;
    }
}

class PostDataDetails {
    private String name;
    private String value;

    public PostDataDetails(String name, String value) {
        this.name = name;
        this.value = value;
    }

    public String getName() {
        return name;
    }

    public String getValue() {
        return value;
    }
}