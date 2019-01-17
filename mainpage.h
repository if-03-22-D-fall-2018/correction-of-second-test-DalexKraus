/** @file mainpage.h
* @brief Beschreibung der Aufgabe Dictionary.
*/
/** @mainpage Dictionary
*
* @author Peter Bauer
*
* @section intro Einführung
* Sie haben die Aufgabe ein Dictionary zu implementieren. Sie sollen in das Dictionary
* Wörter (sortiert oder nicht sortiert) hinzufügen können, im Dictionary nachfragen können,
* ob ein Wort existiert und über alle Wörter im Dictionary iterieren können.
* Die Wörter des Dictionaries sind in einer verketteten Liste zu verwalten. Weiters
* sind doppelte Einträge zu ignorieren.
*
* @section api Die zu implementierenden Funktionen
* - Dictionary new_dictionary(): Erzeugt ein neues leeres Dictionary und gibt
* einen Pointer darauf zurück.
* - delete_dictionary(Dictionary dictionary): Löscht <em>alle</em> Einträge eines Dictionaries.
* und dann das Dictionary selbst.
* - int get_size(Dictionary dictionary): Gibt die Anzahl der Einträge eines dictionaries zurück.
* - void add(Dictionary dictionary, const char* word): Fügt einen Eintrag an das Ende eines Dictionary hinzu,
falls dieser noch nicht existiert, andernfalls macht diese Funktion nichts.
* - bool is_in_dict(Dictionary dictionary, const char* word): Gibt true zurück, wenn Dictionary den
gegebenen Eintrag enthält, sonst false.
* - start_iterating(Dictionary dict), bool has_next(Dictoinary dict) und char* get_next_entry(Dictionary dict)
* dienen dazu, die Einträge des Dictionaries in der Reihenfolge, wie sie gespeichert sind, auszulesen.
* - insert_sorted(Dictionary dict, const char* word) fügt ein neues Wort sofort nach dem Wort im Dictionary
* ein, welches größer als das neue Wort ist.
*
*/
