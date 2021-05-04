package RAC.racontroller.API;

class PostDataDetails {
    private String name;
    private String value;

    PostDataDetails(String name, String value) {
        this.name = name;
        this.value = value;
    }

    String getName() {
        return name;
    }

    String getValue() {
        return value;
    }
}
