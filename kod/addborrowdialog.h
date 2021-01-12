#ifndef ADDBORROWDIALOG_H
#define ADDBORROWDIALOG_H

#include <QDialog>
#include <QTableWidget>


//! Przestrzeń nazw do okna dialogowego dodającego wypożyczenie
namespace Ui {
class addBorrowDialog;
}

/*! \class addBorrowDialog
  \brief Klasa obsługująca dodawanie wypożyczenia
  Zawartość klasy to wszystkie zmienne oraz funkcje użyte w oknie dialogowym służącym do dodania nowego wypożyczenia do programu.
  Klasa dziedziczy publiczne właściwości z klasy QDialog, będącej zawartością biblioteki Qt o tej samej nazwie.
*/
class addBorrowDialog : public QDialog
{
    Q_OBJECT

public:
    /*! \brief Konstruktor klasy ładujący dane do okna dialogowego
    @param *parent wskaźnik na obiekt nadrzędny, jeśli brak to podany nullptr
    @param *clientsTable wskaźnik na tabele zawierającą klientów, w przypadku braku ustawiany na nullptr
    @param *moviesTable wskaźnik na tabele zawierającą filmy, w przypadku braku ustawiany na nullptr
    @param id_setting zmienna bool sprawdzająca, czy opcja wyświetlania ID jest zaznaczona. Domyślnie odznaczona
    */
    explicit addBorrowDialog(QWidget *parent = nullptr, QTableWidget *clientsTable=nullptr, QTableWidget *moviesTable=nullptr, bool id_setting = false);
    ~addBorrowDialog(); //!< Destruktor klasy

    QString borrow_date() const; //!< Zmienna przechowująca date wypożyczenia
    QString return_date() const; //!< Zmienna przechowująca date zwrotu
    QString charge() const; //!< Zmienna przechowująca dzienny koszt wypożyczenia
    QString name() const; //!< Zmienna przechowująca imie klienta
    QString surname() const; //!< Zmienna przechowująca nazwisko klienta
    QString title() const; //!< Zmienna przechowująca tytuł wypożyczanego filmu
    QString chosenClientID() const; //!< Zmienna przechowująca ID klienta
    QString chosenMovieID() const; //!< Zmienna przechowująca ID filmu

    int chosenClientRow() const; //!< Zmienna przechowująca numer aktualnie zaznaczonego wiersza w tabeli klientów
    int chosenMovieRow() const; //!< Zmienna przechowująca numer aktualnie zaznaczonego wiersza w tabeli filmów

    std::pair<int,int> chosenMovie() const; //!< Obiekt przechowujący pozycje wypożyczanego filmu

private slots:

    void on_buttonBox_rejected(); //!< Funkcja wywoływana przy anulowaniu okna przez przycisk

    /*! \brief Funkcja do zaznaczenia całego rzędu w tabeli po kliknięciu na przynależącą do niego komórkę w tabeli filmów
    @param currentRow numer wiersza, którego komórka została zaznaczona
    */
    void on_borrowsMoviesTable_currentCellChanged(int currentRow);

    /*! \brief Funkcja do zaznaczenia całego rzędu w tabeli po kliknięciu na przynależącą do niego komórkę w tabeli klientów
    @param currentRow numer wiersza, którego komórka została zaznaczona
    */
    void on_borrowsClientsTable_currentCellChanged(int currentRow);

    void on_buttonBox_accepted(); //!< Funkcja wywoływana przy potwierdzeniu zmian dokonanych w oknie przez przycisk

    void on_searchClientButton_clicked(); //!< Funkcja obsługująca kliknięcie przycisku wyszukania przy tabeli klientów

    void on_searchMovieButton_clicked(); //!< Funkcja obsługująca kliknięcie przycisku wyszukania przy tabeli filmów

    void on_searchClientField_returnPressed(); //!< Funkcja wywołuje zdarzenie przycisku wyszukania przy tabeli klientów po wciśnięciu klawisza Enter

    void on_searchMovieField_returnPressed(); //!< Funkcja wywołuje zdarzenie przycisku wyszukania przy tabeli filmów po wciśnięciu klawisza Enter

private:
    Ui::addBorrowDialog *ui; //!< Wskaźnik na interfejs wewnątrz klasy
    int clientRow, //!< zmienna zawierająca numer zaznaczonego wiersza tabeli klientów
    movieRow; //!< zmienna zawierająca numer zaznaczonego wiersza tabeli filmów
    QString clientID, //!< zmienna zawierająca ID zaznaczonego klienta
    movieID; //!< zmienna zawierająca ID zaznaczonego filmu
    QTableWidget *moviesTableTemp; //!< wskaźnik na tymczasową tabele filmów

    //! Enum tabeli klientów
    enum CLIENT_COLLUMNS{
        IMIE, /*!< Enum dla imienia klienta */
        NAZWISKO, /*!< Enum dla nazwiska klienta */
        PESEL, /*!< Enum dla numeru pesel klienta */
        TELEFON, /*!< Enum dla numeru telefonu klienta */
        EMAIL, /*!< Enum dla adresu mailowego klienta */
        POSIADANE_FILMY, /*!< Enum dla ilosci filmow posiadanych przez klienta */
        ID_KLIENTA /*!< Enum dla identyfikatora klienta */
    };
    //! Enum tabeli filmów
    enum MOVIE_COLLUMNS{
        TYTUL, /*!< Enum dla tytułu filmu */
        REZYSER, /*!< Enum dla reżysera filmu */
        GATUNEK, /*!< Enum dla gatunku filmu */
        ROK, /*!< Enum dla roku produkcji filmu */
        DOSTEPNE, /*!< Enum dla ilości dostępnych sztuk filmu */
        WYPOZYCZONE, /*!< Enum dla ilości wypożyczonych sztuk filmu */
        ID_FILMU /*!< Enum dla identyfikatora filmu */
    };
};

#endif // ADDBORROWDIALOG_H
