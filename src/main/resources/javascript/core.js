import axios from "axios";
import Vue from "vue";

import BaseCarCalc from "./components/BaseCarCalc";
import PPHCalc from "./components/PPHCalc";

const lodash = require('lodash');

const app = new Vue({
    el: '#body-container',
    components: {
        'base-car-calc': BaseCarCalc,
        'physics-profile-calc': PPHCalc
    },

    created() {
        window.axios = axios.create();
        window._ = lodash;
    }
});