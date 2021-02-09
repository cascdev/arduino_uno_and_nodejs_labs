/******************************************************************************************
* Very simple and small Node Api to communication with Arduino over Shield Ethernet W5100
* Author: Charles Augusto Santos do Carmo  | 2021  
******************************************************************************************/
const axios      = require('axios')
const cors       = require('cors')
const express    = require('express')

// Enviroment's Variables 
const PORT_SERVER   = 3030
const ARDUINO_HOST  = "http://192.168.0.150:3000"  // Arduino's IP + port config on wireless router 
const FRONTEND_HOST = "http://localhost:3000"

const api = axios.create({ baseURL: ARDUINO_HOST })

const app = express()
app.use( express.json() )	

// FronteEnd Server done
const corsOptions = {
  origin: FRONTEND_HOST,
  optionsSuccessStatus: 200
} 
app.use(cors(corsOptions))

// APP ROUTES
app.get('/', async (req, res) => { // localhost:PORT_SERVER
	res.status(200).send(`
		<h1>Type on your browser:</h1>
		<h2>
			localhost:${PORT_SERVER}/arduino
		</h2>
	`)  
})

app.get('/arduino', async (req, res) =>{ // localhost:PORT_SERVER/arduino

	let resp = await api.get('/')
	try{
		let data = await resp.data
		res.status(200).json({
			ok:true,
			dados: data
		})

	}catch( err ){
		res.status(500).json({
			ok: false,
			msg: "Erro na requisição",
			erros: err
		})
	}
})

app.listen( PORT_SERVER, () => {
	console.log(`Server running on localhost: ${PORT_SERVER}`)
})





