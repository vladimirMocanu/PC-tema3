Mocanu-Prejma Vladimir-Georgian
325Cb

								Tema 3 PC

	Am folosit scheletul de cod din laboratorul 10. Tema contine fisierele 
client.c(codul pentru task-uri), requests.c/h pentru a compune mesajele
get si post, parson.c/h pentru parsare JSON, helpers.c/h pentru a compune
efectiv mesajul, dechidere/inchidere conexiune. 
Pentru ca task-urile sunt asemantoare, o sa explic in general cum am implemntat tema.

	Prima data declarat variabilele pe care o sa le folosesc in tema si variabilele
root_value si commit pentru JSON.
Am deschis conexiune(open_connection) pe ip 185.118.200.35, port 8081 
si cam compus mesajul(get sau post) cu datele necesare pentru task-ul corespunzator. 

	Dupa am trimis mesajul catre server(send_to_server) si asteptam raspunsul de la
server(receive_from_server). Retinem raspunsul intr-o variabila(messageFromServer) 
si afisam. In variabila messageJson punem mesajul JSON, si in variabilele cookie1 si
cookie2 copiem "prajituricile" dupa care le concantenam.

	Apelam functia json_parse_string(messageJson) si json_value_get_object(root_value)
pentru a putea accesa elementele din mesajul JSON. 

	Pentru fiecare task completam variabilele data, token, url cu datele necesare pentru 
task-ul respectiv. Fiecare task "pregateste din inainte" datele de care avem nevoie
pentru task-ul urmator. Spre exemplu, la task-ul 2 pregatim sa extragem elementele 
din mesajul JSON, si le folosim pentru task-ul  3. Pentru task-ul 4 nu se intampla
asta(nu am pregatit nimic pentru task-ul 5 pentru ca nu este implementat).

	La final apelam functia free() pentru a elibera memoria.