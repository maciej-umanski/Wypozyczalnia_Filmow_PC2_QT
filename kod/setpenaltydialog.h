#ifndef SETPENALTYDIALOG_H
#define SETPENALTYDIALOG_H

#include <QDialog>

//! Przestrzeń nazw do okna dialogowego zmiany wysokości kary
namespace Ui {
class setPenaltyDialog;
}

/*! \brief Klasa obsługująca zmiane wysokości kary
  Zawartość klasy to wszystkie zmienne oraz funkcje użyte w oknie dialogowym służącym do zmiany wysokości kary za zwrócenie filmu po wyznaczonym terminie.
  Klasa dziedziczy publiczne właściwości z klasy QDialog, będącej zawartością biblioteki Qt o tej samej nazwie.
*/
class setPenaltyDialog : public QDialog
{
    Q_OBJECT

public:
  /*! \brief Konstruktor klasy ładujący dane do okna dialogowego
  @param *parent wskaźnik na obiekt nadrzędny, jeśli brak to podany nullptr
  @param penalty wartość kary, jeśli nie wczytana, to domyślnie wynosi 0
  */
    explicit setPenaltyDialog(QWidget *parent = nullptr, float penalty = 0.00);
    ~setPenaltyDialog(); //!< Destruktor klasy

    float penalty() const; //!< Zmienna przechowująca wysokość kary

private slots:
    void on_buttonBox_accepted();  //!< Funkcja wywoływana przy potwierdzeniu zmian dokonanych w oknie przez przycisk

    void on_buttonBox_rejected();  //!< Funkcja wywoływana przy anulowaniu okna przez przycisk

private:
    Ui::setPenaltyDialog *ui; //!< Wskaźnik na interfejs wewnątrz klasy
};

#endif // SETPENALTYDIALOG_H
