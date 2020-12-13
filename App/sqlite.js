const sqlite3 = require('sqlite3')
const sqlite = require('sqlite')
var moment = require('moment');
require('dotenv').config()


exports.database = {
    db: null,
    connect: async () => this.database.db = await sqlite.open({ filename: process.env.SQLITE_DB_PATH , driver: sqlite3.Database }),
    disconnect: async () => await this.database.db.close(),
    search: async (query) => { 
        try {
            await this.database.connect();
            const result = await this.database.db.all(query);
            await this.database.disconnect();
            return await result;
        } catch (error) {
            console.log(error);
        }
    },
    execute: async (sql) => {
        try {
            await this.database.connect();
            await this.database.db.run(sql);
            await this.database.disconnect();
        } catch (error) {
            console.log(error);
        }
    },
    insertTemp: async (temp, codAquario = 0) => {
        const sql = `INSERT INTO TEMPERATURA (TEMP, COD_AQUARIO) VALUES (${temp}, ${codAquario});`
        this.database.execute(sql);
    }, 
    updateQueue: '',
    updateLastFood: async (codAquario) => {
        const now = moment(new Date()).format("YYYY-MM-DD HH:mm:ss");
        const sql = `UPDATE AQUARIO SET ULTIMO_ALIMENTO = '${now}' WHERE COD_AQUARIO = ${codAquario};`
        this.database.updateQueue += sql;
        setTimeout(() => {
            if (this.database.updateQueue) {
                this.database.execute(this.database.updateQueue);
                console.log('food Database updated');
                this.database.updateQueue = '';
            }
        }, 1000);
    },
    printAllFood: async () => {
        rows = await this.database.search('select * from ALIMENTO');
        console.log(rows);
    }
}
