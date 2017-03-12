export default {
    data() {
        return {
            carId: null,
            carIdMap: []
        }
    },

    created() {
        axios.get('/api/baseCarInfo').then(({data}) => {
            this.carIdMap = _.keyBy(data, function (o) {
                return o.carId;
            });

            this.carId = data[0].carId;
        });
    },

    computed: {
        hash: function () {
            return this.carIdMap[this.carId].hash || -1;
        },

        generatedCode: function() {
            return "<BaseCarId>" + this.hash + "</BaseCarId>";
        }
    }
}