#ifndef ADDCLIENTDIALOG_H
#define ADDCLIENTDIALOG_H

#include <QDialog>

//! Przestrzeń nazw do okna dialogowego dodającego klienta
namespace Ui {
class AddClientDialog;
}

/*!
  \brief Klasa obsługująca dodawanie klienta do bazy
  Zawartość klasy to wszystkie zmienne oraz funkcje użyte w oknie dialogowym służącym do dodania nowego klienta do programu.
  Klasa dziedziczy publiczne właściwości z klasy QDialog, będącej zawartością biblioteki Qt o tej samej nazwie.
*/
class AddClientDialog : public QDialog
{
    Q_OBJECT

public:
    /*! \brief Konstruktor klasy ładujący dane do okna dialogowego
    @param *parent wskaźnik na obiekt nadrzędny, jeśli brak to podany nullptr
    */
    explicit AddClientDialog(QWidget *parent = nullptr);
    ~AddClientDialog(); //!< Destruktor klasy

    QString name() const; //!< Zmienna przechowująca imię klienta
    QString surname() const; //!< Zmienna przechowująca nazwisko klienta
    QString pesel() const; //!< Zmienna przechowująca numer pesel klienta
    QString phone() const; //!< Zmienna przechowująca numer telefonu klienta
    QString email() const; //!< Zmienna przechowująca adres mailowy klienta

private slots:
    void on_buttonBox_accepted(); //!< Wydarzenie przycisku potwierdzenia danych. Sprawdza poprawność i przekazuje dane dalej

    void on_buttonBox_rejected(); //!< Wydarzenie przycisku odrzucenia zmian.

private:
    Ui::AddClientDialog *ui; //!< Wskaźnik na interfejs, umożliwia dostęp do elementów wewnątrz interfejsu
};

#endif // ADDCLIENTDIALOG_H
