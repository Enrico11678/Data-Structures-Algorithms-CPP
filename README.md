# Generic Data Structures & Algorithms Library (C++)
Libreria C++ di strutture dati generiche (Vettori, Liste, Insiemi, Heap, Code a Priorità) con implementazione di algoritmi di ricerca, ordinamento (Heap Sort) e funzioni di ordine superiore (Map, Fold, Traverse). Sviluppato con approccio OOP, template e rigorosi test unitari.

## 🚀 Caratteristiche del Progetto
* **Programmazione Generica**: Utilizzo estensivo di template per il supporto a tipi di dato generici (interi, stringhe, float, ecc.).
* **Paradigma OOP**: Architettura basata su gerarchie di classi con gestione sicura di costruzione, distruzione e assegnamento.
* **Efficienza Algoritmica**: Implementazione di algoritmi di ordinamento come Heap Sort con complessità $O(n \log n)$.

## 🛠️ Strutture Implementate

### Sequenze e Insiemi
* **Vettori**: Gestione dinamica con ridimensionamento automatico ottimizzato.
* **Liste**: Implementazione di liste concatenate con operazioni di inserimento/rimozione in testa e coda.
* **Insiemi Ordinati**: Due diverse implementazioni concrete basate sia su vettori che su liste.

### Heap e Code a Priorità
* **Rappresentazione Implicita**: Gestione di alberi binari tramite vettori per ottimizzare l'occupazione di memoria.
* **Heap**: Funzionalità di ricostruzione e controllo della struttura heap.
* **Code a Priorità**: Supporto per inserimento, rimozione dell'elemento prioritario e cambio di priorità.

## 📂 Organizzazione Modulare
Il codice segue pedissequamente la strutturazione gerarchica richiesta, garantendo ordine e manutenibilità:
* **container/**: Interfacce e classi base.
* **vector/, list/, set/, heap/, pq/**: Implementazioni specifiche delle strutture.
* **zmytest/, zlasdtest/**: Suite di test unitari esterni per la validazione di ogni libreria.
* **Makefile**: Per la compilazione automatizzata del progetto.
