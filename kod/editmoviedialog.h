#ifndef EDITMOVIEDIALOG_H
#define EDITMOVIEDIALOG_H

#include <QDialog>

//! Przestrzeń nazw do okna edytującego istniejący film
namespace Ui {
class editMovieDialog;
}

/*!
  \brief Klasa obsługująca edycje istniejącego filmu
  Zawartość klasy to wszystkie zmienne oraz funkcje użyte w oknie dialogowym służącym do edycji istniejącego w bazie filmu.
  Klasa dziedziczy publiczne właściwości z klasy QDialog, będącej zawartością biblioteki Qt o tej samej nazwie.
*/
class editMovieDialog : public QDialog
{
    Q_OBJECT

public:
  /*! \brief Konstruktor klasy ładujący dane do okna dialogowego
  @param *parent wskaźnik na obiekt nadrzędny, jeśli brak to podany nullptr
  @param title tytuł filmu, domyślnie nullptr
  @param director reżyser filmu, domyślnie nullptr
  @param genre gatunek filmu, domyślnie nullptr
  @param year rok produkcji filmu, domyślnie nullptr
  @param available dostępne sztuki filmu, domyślnie nullptr
  */
    explicit editMovieDialog(QWidget *parent = nullptr,
                             QString title = nullptr,
                             QString director = nullptr,
                             QString genre = nullptr,
                             QString year = nullptr,
                             QString available = nullptr);
    ~editMovieDialog(); //!< Destruktor klasy

    QString title() const; //!< Zmienna przechowująca nowy tytuł filmu
    QString director() const; //!< Zmienna przechowująca nowego reżysera filmu
    QString genre() const; //!< Zmienna przechowująca nowy gatunek filmu
    QString year() const; //!< Zmienna przechowująca nowy rok produkcji filmu
    QString available() const; //!< Zmienna przechowująca nową ilość dostępnych sztuk filmu


private slots:
    void on_buttonBox_accepted(); //!< Wydarzenie przycisku potwierdzenia danych. Sprawdza poprawność i przekazuje dane dalej

    void on_buttonBox_rejected(); //!< Wydarzenie przycisku odrzucenia zmian.

private:
    Ui::editMovieDialog *ui; //!< Wskaźnik na interfejs, umożliwia dostęp do elementów wewnątrz interfejsu
};

#endif // EDITMOVIEDIALOG_H
