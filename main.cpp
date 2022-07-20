#include <iostream>
#include <malloc.h>

/* Datenstruktur eines Listenelements */
typedef struct eintrag {
    int key;
    struct eintrag * p_prev;
    struct eintrag * p_next;
} eintrag_t;

/* Datenstruktur mit Informationen ueber die Liste */
typedef struct {
    eintrag_t * p_head;
    eintrag_t * p_tail;
    eintrag_t * p_curr;
    int length;
} liste_t;

//Legt den Speicher für ein Listenelement an,
//speichert den key-Wert im Element.
//Gibt einen Zeiger auf das neues Listenelement zur ̈uck.
eintrag_t * create_element (int key){
    auto *element = new eintrag_t;
    element->p_prev = nullptr;
    element->p_next = nullptr;
    element->key = key;
    return element;
};

//F ̈ugt ein Element sortiert in die Liste ein.
//Zuerst wird die Position gesucht, an der das Listenelement
//eingef ̈ugt werden soll.
//Es sind 3 M ̈oglichkeiten zu unterscheiden, am Anfang der Liste,
//mitten in der Liste oder am Ende der Liste.
//Anschließend wird das Element in die Liste eingef ̈ugt.
void insert_element(liste_t * liste, eintrag_t * p_insert){
    if(liste->length == 0){                                                            //wenn liste leer ist
        liste->p_head = p_insert;
        liste->p_tail = p_insert;
        liste->length++;
        return;
    }
    if(p_insert->key < liste->p_head->key){                                             //wenn element kleiner als das erstes element ist
        p_insert->p_next = liste->p_head;                                               //[p_insert] -> p_head
        liste->p_head->p_prev = p_insert;                                               //[p_inser] <- p_head
        liste->p_head = p_insert;                                                       //[p_insert] wird neuer p_head
        liste->length++;                                                                //liste wird um 1 vergrößert
        return;
    }
    if(p_insert->key > liste->p_tail->key){                                            //wenn element größer als das letzte element ist
        p_insert->p_prev = liste->p_tail;                                              //[p_insert] -> p_tail(vorgänger)
        liste->p_tail->p_next = p_insert;                                              //[p_insert] <- p_tail
        liste->p_tail = p_insert;                                                      //[p_insert] wird neuer p_tail
        liste->length++;                                                               //liste wird um 1 vergrößert
        return;
    }
        //wenn das element in die mitte der liste kommt
    liste->p_curr = liste->p_head;
    while(liste->p_curr->key < p_insert->key){                                      //finde die richtige stelle zum einfügen
        liste->p_curr = liste->p_curr->p_next;
    }
    p_insert->p_next = liste->p_curr;                                               //neu -> alter Knoten
    p_insert->p_prev = liste->p_curr->p_prev;                                       //vorgänger vom alten Knoten <- neu -> alter Knoten
    p_insert->p_next->p_prev = p_insert;                                            //neu <- alter Knoten
    p_insert->p_prev->p_next = p_insert;                                            //vorgänger vom alten Knoten -> neu
    liste->length++;
};

//Gibt alle Listen-Elemente aus
void print_list(liste_t liste){
    liste.p_curr = liste.p_head;
    for (int i = 0; i < liste.length; ++i) {
        std::cout << liste.p_curr->key << "->";
        liste.p_curr = liste.p_curr->p_next;
    }
};

int main() {
    int val = 0;
    liste_t liste;

    liste.length = 0;
    liste.p_curr = nullptr;
    liste.p_head = nullptr;
    liste.p_tail = nullptr;

    while (1){
        std::cout << "gebe Key ein" << std::endl;

        std::cin >> val;
        if (val == 0){
            print_list(liste);
            return 0;
        }
        eintrag_t *neu = create_element(val);
        insert_element(&liste, neu);
    }
}
