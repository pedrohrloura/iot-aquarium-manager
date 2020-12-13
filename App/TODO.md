- [ ] Sistema de de Alimentação Automática e Remota
	- [ ] Liga o Servo Motor e Joga Alimento
		- [x] Manualmente
		- [ ] Alimento Periodicamente
			- [x] Implementar  CronJs para Agenda de Alimentação
			- [ ] A cada 1 hora executas as seguintes queries(está 1 min para testes)
				- [x] Verificar se existe algum aquário que para ser alimentado
				- [x] Verificar o melhor jeito de criar novas tasks
					- [x] Criar um método que atualiza no BD mais de um aquário por vez
		- [x] Verificar o identificador do aquário no código do ESP32 - Usamos um ESP para n Aquarioes.
- [ ] Agente de Temperatura
	- [ ] Alerta quando a temperatura está maior/menor(tolerância) do que a ideal(Pedro)
		** A Temperatura ideal para cada aquário é atualizada a cada 12 horas
		- [x] Verifica se está dentro dos contrains(limite)
		- [x] Se não estivar Emite um alerta

- [ ] Diagrama Elétrico (Tinkercad) - (Tom)

Código Fonte
	- [ ] Hardware (Pedro, Ian)
	- [ ] Back-end (Pedro, Ian, Fernando)

- [ ] Estrutura da Entrega
	- [ ] Projeto
		- [ ] Diagrama Elétrico (Tinkercad) - (Tom)
		- [ ] Listagem dos Programas(Código Fonte) - (Todos)
		- [ ] Membros do Grupo(txt) - (Todos)
		- [ ] Scrum - Utilizamos o Trelo (Todos)
		- [ ] Relatório - (Oque Implementamos, Quais Dores, Conclusão) - (Tom)
		- [ ] Vídeos&Fotos - (Tom)

- [ ] Compactar arquivos para envio
