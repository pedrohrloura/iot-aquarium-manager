const { connect, Request } = require("tedious");
const TYPES = require('tedious').TYPES;
require('dotenv').config()
//DATABASE
var config = {
    server: process.env.DB_SERVER,
    authentication: {
        options: {
            userName: process.env.DB_USERNAME,
            password: process.env.DB_PASSWORD
        },
        type: "default"
    },
    options: {
        validateBulkLoadParameters: true,
        database: process.env.DB_DATABASE,
        encrypt: true,
        trustServerCertificate: true
    }
};

exports.database = {
    connection: null,
    connect: () => {
        this.database.connection = new connect(config);
        this.database.on("connect", err => {
            if (err) console.error(err.message);
            else console.log("Connected to database");
        });
    },
    insertTemp: (temp, codAquario = 0) => {
        const request = new Request("INSERT INTO TEMPERATURA (TEMP, COD_AQUARIO) VALUES (@TEMP, @COD_AQUARIO);", function (err) {
            if (err) {
                console.log(err);
            }
        });
        request.addParameter('TEMP', TYPES.Int, temp);
        request.addParameter('COD_AQUARIO', TYPES.Int, codAquario);
        console.log(`Values ​​entered successfully in database`)
        this.database.connection.execSql(request);
        this.database.connection.close();
    },
    updateLastFood: (codAquario) => {
        const request = new Request("UPDATE AQUARIO SET ULTIMO_ALIMENTO = @ULTIMO_ALIMENTO WHERE COD_AQUARIO = @COD_AQUARIO;", function (err) {
            if (err) {
                console.log(err);
            }
        });
        let time = moment(new Date()).format("YYYY-MM-DD HH:mm:ss");
        request.addParameter('ULTIMO_ALIMENTO', TYPES.DateTime, time);
        request.addParameter('COD_AQUARIO', TYPES.Int, codAquario);
        console.log(`Valunpm install sqlite3es ​​entered successfully in database`)
        this.database.connection.execSql(request);
        this.database.connection.close();
    }

}
