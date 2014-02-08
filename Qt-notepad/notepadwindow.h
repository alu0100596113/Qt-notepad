#ifndef NOTEPADWINDOW_H
#define NOTEPADWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit> //Clase que nos permite trabajar con un cuadro de texto
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QFontDialog>
#include <QClipboard>
#include <QKeySequence>
#include <QMessageBox>

class NotepadWindow : public QMainWindow
{
    Q_OBJECT

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

public slots:
    void alCerrar();
    void alAbrir();
    void alGuardar();
    void alFuente();
    void alAyuda();
private:
    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QPlainTextEdit* txtEditor_;
    QAction* actArchivoAbrir_;
    QAction* actArchivoGuardar_;
    QAction* actArchivoCerrar_;


    QMenu* mnuFormato_;
    QAction* actFormatoFuente_;
    QMenu* mnuEditar_;
    QAction* actEditarCopiar_;
    QAction* actEditarPegar_;
    QClipboard * portapapeles_;

    QAction* actEditarDeshacer_;
    QAction* actEditarRehacer_;
    QAction* actEditarCortar_;
    QMenu* mnuAyuda_;
    QAction* actMostrarAyuda_;

};

#endif // NOTEPADWINDOW_H
