package me.leorblx.webtools.controllers;

import com.google.gson.Gson;
import com.google.gson.JsonArray;
import com.google.gson.JsonObject;
import me.leorblx.webtools.NativeBridge;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api")
public class ApiController {
    private final Gson gson = new Gson();
    private final NativeBridge nativeBridge;

    @Autowired
    public ApiController(NativeBridge nativeBridge) {
        this.nativeBridge = nativeBridge;
    }

    @RequestMapping("baseCarInfo")
    public ResponseEntity<String> baseCarInfo() {
        JsonArray jsonArray = new JsonArray();

        for (String carId : nativeBridge.getBaseCarNames()) {
            long hash = nativeBridge.getBaseCar(carId);

            JsonObject object = new JsonObject();
            object.addProperty("carId", carId);
            object.addProperty("hash", hash);

            jsonArray.add(object);
        }

        HttpHeaders headers = new HttpHeaders();
        headers.set(HttpHeaders.CONTENT_TYPE, "application/json");

        return new ResponseEntity<>(gson.toJson(jsonArray), headers, HttpStatus.OK);
    }

    @RequestMapping("physicsInfo")
    public ResponseEntity<String> physicsInfo() {
        JsonArray jsonArray = new JsonArray();

        for (String carId : nativeBridge.getAllCarNames()) {
            long hash = nativeBridge.calculateCarHash(carId);

            JsonObject object = new JsonObject();
            object.addProperty("carId", carId);
            object.addProperty("hash", hash);

            jsonArray.add(object);
        }

        HttpHeaders headers = new HttpHeaders();
        headers.set(HttpHeaders.CONTENT_TYPE, "application/json");

        return new ResponseEntity<>(gson.toJson(jsonArray), headers, HttpStatus.OK);
    }
}
