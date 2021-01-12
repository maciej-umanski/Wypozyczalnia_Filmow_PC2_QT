#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//! Przestrzeń nazw do głównego okna programu
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/*!
  \brief Klasa obsługująca główne okno programu
  Zawartość klasy to wszystkie zmienne oraz funkcje użyte w głównym oknie programu.
  Klasa dziedziczy publiczne właściwości z klasy QMainWindow, będącej zawartością biblioteki Qt o tej samej nazwie.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
  /*! \brief Konstruktor klasy ładujący dane do okna programu
  @param *parent wskaźnik na obiekt nadrzędny, jeśli brak to podany nullptr
  */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); //!< Destruktor klasy

private slots:
    /*! \brief Funkcja zamykająca program
    @param event wydarzenie zamknięcia aplikacji
    */
    void closeEvent(QCloseEvent *event);

    void on_addClientButton_clicked(); //!< Funkcja wydarzenia przycisku dodania klienta.

    void on_delClientButton_clicked(); //!< Funkcja wydarzenia przycisku usunięcia klienta.

    void on_delMovieButton_clicked(); //!< Funkcja wydarzenia przycisku usunięcia filmu

    void on_addMovieButton_clicked(); //!< Funkcja wydarzenia przycisku dodania filmu.

    void on_editClientButton_clicked(); //!< Funkcja wydarzenia przycisku edycji klienta.

    void on_editMovieButton_clicked(); //!< Funkcja wydarzenia przycisku edycji filmu.

    void on_addBorrowButton_clicked(); //!< Funkcja wydarzenia przycisku dodania wypożyczenia

    void on_searchClientButton_clicked(); //!< Funkcja wydarzenia przycisku wyszukania klienta.

    void on_searchBorrowsButton_clicked(); //!< Funkcja wydarzenia przycisku wyszukania wypożyczenia.

    void on_searchMovieButton_clicked(); //!< Funkcja wydarzenia przycisku wyszukania filmu.

    void on_searchBorrowField_returnPressed(); //!< Funkcja wydarzenia pola wyszukiwania wypożyczenia przy wciśnięciu klawisza Enter.

    void on_searchClientField_returnPressed(); //!< Funkcja wydarzenia pola wyszukiwania klienta przy wciśnięciu klawisza Enter.

    void on_searchMovieField_returnPressed(); //!< Funkcja wydarzenia pola wyszukiwania filmu przy wciśnięciu klawisza Enter.

    void on_delBorrowButton_clicked(); //!< Funkcja wydarzenia przycisku usunięcia wypożyczenia.

    void on_editBorrowButton_2_clicked(); //!< Funkcja wydarzenia przycisku edycji wypożyczenia.

    void on_actionZapisz_do_pliku_triggered(); //!< Funkcja wywoływana przez opcję zapisu baz do pliku z menu.

    void on_actionWczytaj_bazy_z_pliku_triggered();  //!< Funkcja wywoływana przez opcję wczytania baz z pliku z menu.

    /*! \brief Funkcja podświetlająca zaległe wypożyczenia innym kolorem
    @param arg1 zmienna typu bool do sprawdzenia, czy opcja w menu jest zaznaczona.
    */
    void on_actionPod_wietlaj_zaleg_e_toggled(bool arg1);

    void on_actionUstal_wysoko_kary_triggered(); //!< Funkcja obsługująca opcje z menu odnośnie ustalenia wysokości kary za poterminowy zwrot wypożyczenia.

    void on_actionShow_Last_IDs_triggered(); //!< Funkcja obsługująca opcje wyświetlającą ostatnie użyte ID w bazie.

    void on_actionShow_penalty_triggered(); //!< Funkcja obsługująca opcje wyświetlającą aktualną wysokość kary za dzień zwłoki

    /*! \brief Funkcja wyświetlająca ukryte kolumny z ID wpisów bazy.
    @param arg1 zmienna typu bool do sprawdzenia, czy opcja w menu jest zaznaczona.
    */
    void on_actionShow_IDs_toggled(bool arg1);

    void on_actionWyjd_triggered(); //!< Funkcja wywołująca akcje zamknięcia okna w menu.

    /*! \brief Funkcja obsługująca typ wyświetlanych wypożyczeń (wyszystkie/zaległe/aktualne).
    @param index numer pola combobox
    */
    void on_comboBox_currentIndexChanged(int index);

    /*! \brief Funkcja obsługująca opcje menu wyświetlającą kolumne ze statusem zwrócenia wypożyczenia (zwrócone/aktywne)
    @param arg1 zmienna typu bool do sprawdzenia, czy opcja w menu jest zaznaczona.
    */
    void on_actionPokazuj_Status_Zwr_cenia_toggled(bool arg1);

    /*! \brief Funkcja podświetlająca zwrócone wypożyczenia
    @param arg1 zmienna typu bool do sprawdzenia, czy opcja w menu jest zaznaczona.
    */
    void on_actionPod_wietlaj_zwr_cone_toggled(bool arg1);

    /*! \brief Funkcja podświetlająca aktualne (niezaległe) wypożyczenia kolorem.
    @param arg1 zmienna typu bool do sprawdzenia, czy opcja w menu jest zaznaczona.
    */
    void on_actionPod_wietlaj_aktualne_niezaleg_e_toggled(bool arg1);

private:

    float penalty; //!< Zmienna przechowująca wartość kary za poterminowy zwrot
    int clients_lastID, //!< Zmienna przechowująca ostatnie użyte ID w tabeli klientów
    movies_lastID; //!< Zmienna przechowująca ostatnie użyte ID w tabeli filmów

    Ui::MainWindow *ui; //!< Wskaźnik na interfejs, umożliwia dostęp do elementów wewnątrz interfejsu

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
        WYPOZYCZONE,  /*!< Enum dla ilości wypożyczonych sztuk filmu */
        ID_FILMU /*!< Enum dla identyfikatora filmu */
    };

    //! Enum tabeli wypożyczeń
    enum BORROW_COLLUMNS{
        IMIE_WYP, /*!< Enum dla imienia klienta wypożyczającego film */
        NAZWISKO_WYP, /*!< Enum dla nazwiska klienta wypożyczającego film */
        TITLE, /*!< Enum dla tytułu wypożyczonego filmu */
        DATA_WYPOZYCZENIA, /*!< Enum dla daty wypożyczenia filmu */
        DATA_ZWROTU, /*!< Enum dla daty zwrotu filmu */
        KOSZT,  /*!< Enum dla kosztu wypożyczenia filmu */
        ID_FILMU_WYP,  /*!< Enum dla ID wypożyczonego filmu */
        ID_KLIENTA_WYP, /*!< Enum dla ID wypożyczającego klienta */
        ZWROCONE /*!< Enum dla informacji, czy dany film został zwrócony */
    };

};
#endif // MAINWINDOW_H
