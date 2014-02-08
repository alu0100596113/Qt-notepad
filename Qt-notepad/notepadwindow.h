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

class NotepadWindow : public QMainWindow
{
    Q_OBJECT

public:
    NotepadWindow(QWidget *parent = 0);
    ~NotepadWindow();

private slots:
    void alAbrir();
    void alGuardar();
    void alFuente();

private:
    QMenuBar* mainMenu_;
    QMenu* mnuArchivo_;
    QPlainTextEdit* txtEditor_;
    QAction* actArchivoAbrir_;
    QAction* actArchivoGuardar_;

    QMenu* mnuFormato_;
    QAction* actFormatoFuente_;
    QMenu* mnuEditar_;
    QAction* actEditarCopiar_;
    QAction* actEditarPegar_;
    QClipboard * portapapeles_;

};

#endif // NOTEPADWINDOW_H
