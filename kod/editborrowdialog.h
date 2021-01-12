#ifndef EDITBORROWDIALOG_H
#define EDITBORROWDIALOG_H

#include <QDialog>

//! Przestrzeń nazw do okna edytującego istniejące wypożyczenie
namespace Ui {
class editBorrowDialog;
}

/*!
  \brief Klasa obsługująca edycje istniejącego wypożyczenia
  Zawartość klasy to wszystkie zmienne oraz funkcje użyte w oknie dialogowym służącym do edycji istniejącego w bazie wypożyczenia.
  Klasa dziedziczy publiczne właściwości z klasy QDialog, będącej zawartością biblioteki Qt o tej samej nazwie.
*/
class editBorrowDialog : public QDialog
{
    Q_OBJECT

public:
  /*! \brief Konstruktor klasy ładujący dane do okna dialogowego
  @param *parent wskaźnik na obiekt nadrzędny, jeśli brak to podany nullptr
  @param returndate data zwrotu pobrana z istniejącego wypożyczenia, domyślnie nullptr
  */
    explicit editBorrowDialog(QWidget *parent = nullptr, QString returndate = nullptr);
    ~editBorrowDialog(); //!< Destruktor klasy

    QString returndate() const; //!< Zmienna przechowująca nową date zwrotu

private slots:
    void on_buttonBox_rejected(); //!< Wydarzenie przycisku potwierdzenia danych. Sprawdza poprawność i przekazuje dane dalej

    void on_buttonBox_accepted(); //!< Wydarzenie przycisku odrzucenia zmian.

private:
    Ui::editBorrowDialog *ui; //!< Wskaźnik na interfejs, umożliwia dostęp do elementów wewnątrz interfejsu
};

#endif // EDITBORROWDIALOG_H
