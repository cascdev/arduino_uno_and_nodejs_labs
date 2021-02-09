
//Função para buscar dados do Arduino | TESTE para buscar dados do Arduino//////////////////////////////////
let getData = async () => {

	try{

		const resp = await api.get('/')
		let dados = await resp.data
		console.log( dados )			
	}
	catch( err ){ 

		const erros =	
		{
			ok: false,
			msgError: "Erro na requisição!",
			errors:err
		}
		console.log( erros )
	}
}
//getData()
module.exports = {getData}