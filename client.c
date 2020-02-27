// Mocanu-Prejma Vladimir-Georgian
// 325Cb

#include <stdio.h>      
#include <stdlib.h>     
#include <unistd.h>     
#include <string.h>     
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netdb.h>      
#include <arpa/inet.h>
#include "parson.h"
#include "helpers.h"
#include "requests.h"

int main(int argc, char *argv[])
{
    //declaram toate variabilele
    char *message;
    char *messageFromServer;
    char *messageJson;
    char *cookie1;
    char *cookie2;
    char token[520];
    char url[30];
    char data[100];
    int sockfd;

    JSON_Value *root_value;
    JSON_Object *commit;

    //Task1

    //pentru a compune mesajul
    sprintf(url, "%s", "/task1/start");

    //dechidem o conexiune nou pe ip 185.118.200.35, port 8081
    //si compunem mesajul corespunzator
    sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request("185.118.200.35", url, NULL, NULL, NULL);

    //il trimitem
    send_to_server(sockfd, message);

    //primim raspunsul si il afisam
    messageFromServer = receive_from_server(sockfd);
    printf("%s\n\n\n", messageFromServer );

    //extragem ce avem nevoie din enunt pentru task-ul urmator
    messageJson = strndup(messageFromServer + 483, 487);
    cookie1 = strndup(messageFromServer + 76, 128);
    cookie2 = strndup(messageFromServer + 275, 43);

    //concatenam stringurile
    strcat(cookie1, "; ");
    strcat(cookie1, cookie2);

    //pentru a extrage din messageJson datele de care avem nevoie
    root_value = json_parse_string(messageJson);
    commit = json_value_get_object(root_value);

    //inchidem connexinea
    close_connection(sockfd);


    //Task2

    //completam cu datele necesare pentru task
    sprintf(data, "username=%s&password=%s",
            json_object_dotget_string(commit, "data.username"),
            json_object_dotget_string(commit, "data.password"));
    sprintf(url, "%s", json_object_get_string(commit, "url"));

    //dechidem o conexiune nou pe ip 185.118.200.35, port 8081
    //si compunem mesajul corespunzator
    sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
    message = compute_post_request("185.118.200.35", url, data, cookie1);

    //trimitem mesajul catre server

    send_to_server(sockfd, message);

    //primim raspunsul si il afisam
    messageFromServer = receive_from_server(sockfd);
    printf("%s\n\n\n", messageFromServer );

    //extragem ce avem nevoie din enunt pentru task-ul urmator
    messageJson = strndup(messageFromServer + 520, 1464);
    cookie1 = strndup(messageFromServer + 76, 164);
    cookie2 = strndup(messageFromServer + 311, 43);

    //concatenam stringurile
    strcat(cookie1, "; ");
    strcat(cookie1, cookie2);

    json_value_free(root_value);
    //pentru a extrage din messageJson datele de care avem nevoie
    root_value = json_parse_string(messageJson);
    commit = json_value_get_object(root_value);

    //inchidem connexinea
    close_connection(sockfd);


    //Task3
    //
    //completam cu datele necesare pentru task
    sprintf(data, "raspuns1=omul&raspuns2=numele&id=%s",
            json_object_dotget_string(commit, "data.queryParams.id"));
    sprintf(url, "%s", json_object_get_string(commit, "url"));
    sprintf(token, "%s", json_object_dotget_string(commit, "data.token"));

    //dechidem o conexiune nou pe ip 185.118.200.35, port 8081
    //si compunem mesajul corespunzator
    sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request("185.118.200.35", url, data, cookie1, token);

    //trimitem mesajul catre server
    send_to_server(sockfd, message);

    //primim raspunsul si il afisam
    messageFromServer = receive_from_server(sockfd);
    printf("%s\n\n\n", messageFromServer );

    //extragem ce avem nevoie din enunt pentru task-ul urmator
    messageJson = strndup(messageFromServer + 547, 412);
    cookie1 = strndup(messageFromServer + 76, 192);
    cookie2 = strndup(messageFromServer + 339, 43);

    strcat(cookie1, "; ");
    strcat(cookie1, cookie2);

    json_value_free(root_value);

    //pentru a extrage din messageJson datele de care avem nevoie
    root_value = json_parse_string(messageJson);
    commit = json_value_get_object(root_value);

    //inchidem connexinea
    close_connection(sockfd);


    //Task4

    sprintf(url, "%s", json_object_get_string(commit, "url"));

    //dechidem o conexiune nou pe ip 185.118.200.35, port 8081
    // si compunem mesajul corespunzator
    sockfd = open_connection("185.118.200.35", 8081, AF_INET, SOCK_STREAM, 0);
    message = compute_get_request("185.118.200.35", url, NULL, cookie1, token);

    //trimitem mesajul
    send_to_server(sockfd, message);

    //primim raspunsul si il afisam
    messageFromServer = receive_from_server(sockfd);
    printf("%s\n\n\n", messageFromServer );

    //inchidem connexinea
    close_connection(sockfd);

    //eliberam memoria
    json_value_free(root_value);
    free(message);
    free(messageFromServer);
    free(messageJson);
    free(cookie1);

    return 0;
}
