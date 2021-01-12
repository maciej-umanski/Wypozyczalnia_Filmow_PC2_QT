#ifndef EDITCLIENTDIALOG_H
#define EDITCLIENTDIALOG_H

#include <QDialog>

//! Przestrzeń nazw do okna edytującego istniejącego klienta
namespace Ui {
class editClientDialog;
}

/*!
  \brief Klasa obsługująca edycje istniejącego klienta
  Zawartość klasy to wszystkie zmienne oraz funkcje użyte w oknie dialogowym służącym do edycji istniejącego w bazie klienta.
  Klasa dziedziczy publiczne właściwości z klasy QDialog, będącej zawartością biblioteki Qt o tej samej nazwie.
*/
class editClientDialog : public QDialog
{
    Q_OBJECT

public:
  /*! \brief Konstruktor klasy ładujący dane do okna dialogowego
  @param *parent wskaźnik na obiekt nadrzędny, jeśli brak to podany nullptr
  @param name imie klienta, domyślnie nullptr
  @param surname nazwisko klienta, domyślnie nullptr
  @param pesel numer pesel klienta, domyślnie nullptr
  @param phone numer telefonu klienta, domyślnie nullptr
  @param email adres mailowy klienta, domyślnie nullptr
  */
    explicit editClientDialog(QWidget *parent = nullptr,
                              QString name = nullptr,
                              QString surname = nullptr,
                              QString pesel = nullptr,
                              QString phone = nullptr,
                              QString email = nullptr);
    ~editClientDialog(); //!< Destruktor klasy

    QString name() const; //!< Zmienna przechowująca nowe imie klienta
    QString surname() const; //!< Zmienna przechowująca nowe nazwisko klienta
    QString pesel() const; //!< Zmienna przechowująca nowy numer pesel klienta
    QString phone() const; //!< Zmienna przechowująca nowy numer telefonu klienta
    QString email() const; //!< Zmienna przechowująca nowy adres mailowy klienta

private slots:
    void on_buttonBox_accepted(); //!< Wydarzenie przycisku potwierdzenia danych. Sprawdza poprawność i przekazuje dane dalej

    void on_buttonBox_rejected(); //!< Wydarzenie przycisku odrzucenia zmian.

private:
    Ui::editClientDialog *ui; //!< Wskaźnik na interfejs, umożliwia dostęp do elementów wewnątrz interfejsu
};

#endif // EDITCLIENTDIALOG_H
