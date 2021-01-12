#ifndef ADDMOVIEDIALOG_H
#define ADDMOVIEDIALOG_H

#include <QDialog>

//! Przestrzeń nazw do okna dialogowego dodającego film
namespace Ui {
class addMovieDialog;
}

/*!
  \brief Klasa obsługująca dodawanie filmu do bazy
  Zawartość klasy to wszystkie zmienne oraz funkcje użyte w oknie dialogowym służącym do dodania nowego filmu do programu.
  Klasa dziedziczy publiczne właściwości z klasy QDialog, będącej zawartością biblioteki Qt o tej samej nazwie.
*/
class addMovieDialog : public QDialog
{
    Q_OBJECT

public:
  /*! \brief Konstruktor klasy ładujący dane do okna dialogowego
  @param *parent wskaźnik na obiekt nadrzędny, jeśli brak to podany nullptr
  */
    explicit addMovieDialog(QWidget *parent = nullptr);
    ~addMovieDialog(); //!< Destruktor klasy

    QString title() const; //!< Zmienna przechowująca tytuł filmu
    QString director() const; //!< Zmienna przechowująca reżysera filmu
    QString genre() const; //!< Zmienna przechowująca gatunek filmu
    QString year() const; //!< Zmienna przechowująca rok produkcji filmu
    QString available() const; //!< Zmienna przechowująca ilość dostępnych sztuk filmu

private slots:
    void on_buttonBox_accepted(); //!< Wydarzenie przycisku potwierdzenia danych. Sprawdza poprawność i przekazuje dane dalej

    void on_buttonBox_rejected(); //!< Wydarzenie przycisku odrzucenia zmian.

private:
    Ui::addMovieDialog *ui; //!< Wskaźnik na interfejs, umożliwia dostęp do elementów wewnątrz interfejsu
};

#endif // ADDMOVIEDIALOG_H
