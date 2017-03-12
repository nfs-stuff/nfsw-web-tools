package me.leorblx.webtools.controllers;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class CarController {
    @RequestMapping("/basecar-calculator")
    public String baseCarCalc() {
        return "baseCarId";
    }

    @RequestMapping("/pph-calculator")
    public String physicsHashCalc() {
        return "physicsProfileHash";
    }
}
