module.exports = {
    entry: "./src/main/resources/javascript/core.js",
    output: {
        path: "./src/main/resources/static/js",
        filename: "bundled.js"
    },
    module: {
        loaders: [
            {
                test: /\.css$/,
                use: ['style-loader', 'css-loader']
            },
            {
                test: /\.js$/,
                exclude: /node_modules/,
                loader: 'babel-loader'
            }
        ]
    },
    resolve: {
        alias: {
            vue: '../../../../node_modules/vue/dist/vue.js'
        }
    }
};