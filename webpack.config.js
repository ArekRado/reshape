const path = require('path')
const HtmlWebpackPlugin = require('html-webpack-plugin')

const isProd = process.env.NODE_ENV === 'production'

module.exports = {
  entry: './src/index.bs.js',
  mode: isProd ? 'production' : 'development',
  output: {
    path: path.join(__dirname, 'bundledOutputs'),
    filename: '[name].js',
  },
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /(node_modules|bower_components)/,
        use: {
          loader: 'babel-loader',
          options: {
            presets: ['@babel/preset-env'],
          },
        },
      },
    ],
  },
  plugins: [new HtmlWebpackPlugin()],
}
