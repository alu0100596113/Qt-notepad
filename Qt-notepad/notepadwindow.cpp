#include "notepadwindow.h"

NotepadWindow::NotepadWindow(QWidget *parent)
    : QMainWindow(parent)
{
    txtEditor_ = new QPlainTextEdit(this);//this: Es el padre, es este caso QMainWindow

    setCentralWidget(txtEditor_); //setCentralWidget hereda de QMainWindows
    mainMenu_ = new QMenuBar(this);// Se pide memoeri par auna barra vacia donde colocar menu
    //La funcion tr traducela cadena de texto y nos permite en una version posterior traducir el programa
    //&: Alt + letra: El & nos permite el acceso rapido mediante teclado
    mnuArchivo_ = new QMenu(tr("&Archivo"), this);
    mainMenu_->addMenu(mnuArchivo_);
    setMenuBar(mainMenu_);

//*****
    //Menu Archivo

    actArchivoAbrir_ = new QAction(tr("&Abrir"), this);
    actArchivoAbrir_ ->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    mnuArchivo_->addAction(actArchivoAbrir_);

    actArchivoGuardar_ = new QAction(tr("&Guardar"), this);
    actArchivoGuardar_ ->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    mnuArchivo_->addAction(actArchivoGuardar_);

    actArchivoCerrar_ = new QAction(tr("&Cerrar"), this);
    actArchivoCerrar_ ->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuArchivo_->addAction(actArchivoCerrar_);

//*****
    //Menu Editar

    mnuEditar_ = new QMenu(tr("&Editar"));
    mainMenu_->addMenu(mnuEditar_);

    actEditarCopiar_ = new QAction(tr("&Copiar"), this);
    actEditarCopiar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_C));
    mnuEditar_->addAction(actEditarCopiar_);

    actEditarPegar_ = new QAction(tr("&Pegar"), this);
    actEditarPegar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));
    mnuEditar_->addAction(actEditarPegar_);

    actEditarDeshacer_ = new QAction(tr("&Deshacer"), this);
    actEditarDeshacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    mnuEditar_->addAction(actEditarDeshacer_);

    actEditarRehacer_ = new QAction(tr("&Rehacer"), this);
    actEditarRehacer_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    mnuEditar_->addAction(actEditarRehacer_);

    actEditarCortar_ = new QAction(tr("&Cortar"), this);
    actEditarCortar_->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_X));
    mnuEditar_->addAction(actEditarCortar_);

//*****
    //Menu formato

    mnuFormato_ = new QMenu(tr("&Formato"));
    mainMenu_->addMenu(mnuFormato_);

    actFormatoFuente_ = new QAction(tr("&Fuente"), this);
    mnuFormato_->addAction(actFormatoFuente_);
//*****
    //Menu Ayuda

    mnuAyuda_ = new QMenu(tr("&Ayuda"));
    mainMenu_->addMenu(mnuAyuda_);

    actMostrarAyuda_ = new QAction(tr("&Mostrar"), this);
    mnuAyuda_->addAction(actMostrarAyuda_);

//*****

    //Conexiones
    connect(actArchivoAbrir_, SIGNAL(triggered()), this, SLOT(alAbrir()));
    connect(actArchivoGuardar_, SIGNAL(triggered()), this, SLOT (alGuardar()));
    connect(actArchivoCerrar_, SIGNAL(triggered()), this, SLOT (alCerrar()));
    connect(actEditarCopiar_, SIGNAL(triggered()), txtEditor_, SLOT(copy()));
    connect(actEditarPegar_, SIGNAL(triggered()), txtEditor_, SLOT(paste()));
    connect(actFormatoFuente_, SIGNAL(triggered()), this, SLOT(alFuente()));
    connect(actEditarDeshacer_, SIGNAL(triggered()), txtEditor_, SLOT(undo()));
    connect(actEditarRehacer_, SIGNAL(triggered()), txtEditor_, SLOT(redo()));
    connect(actEditarCortar_, SIGNAL(triggered()), txtEditor_, SLOT(cut()));
    connect(actMostrarAyuda_, SIGNAL(triggered()), this, SLOT(alAyuda()));
}


NotepadWindow::~NotepadWindow()
{
    mainMenu_->deleteLater();
    actArchivoAbrir_->deleteLater();
    actArchivoGuardar_->deleteLater();
    mnuArchivo_->deleteLater();
    actEditarCopiar_->deleteLater();
    actEditarPegar_->deleteLater();
    mnuEditar_->deleteLater();
    actFormatoFuente_->deleteLater();
    mnuFormato_->deleteLater();
    txtEditor_->deleteLater();
}

void NotepadWindow::alAbrir()
{
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getOpenFileName(this,
                                                 tr("Abrir Archivo de texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano (*.txt)"));
    if(nombreArchivo != ""){
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if(archivo.open(QFile::ReadOnly)){
            //Di se pudo abrir el archivo, lo leemos y colocamos
            txtEditor_->setPlainText((archivo.readAll()));
            //Se cierra el fichero
            archivo.close();
        }
    }
}

void NotepadWindow::alCerrar()
{
       QMessageBox msgExit;
       msgExit.setText("¿Qué desea hacer?");
       msgExit.addButton("Guardar", QMessageBox::ApplyRole);
       msgExit.addButton("Salir sin guardar", QMessageBox::NoRole);
       int option = msgExit.exec(); //Devuelve el entero
       if(option == 0)
       {
           alGuardar();
       }
       else if (option == 1)
           exit(0);
}

void NotepadWindow::alGuardar()
{
    QString nombreArchivo;
    nombreArchivo = QFileDialog::getSaveFileName(this, tr("Guardar archivo como texto plano"),
                                                 "",
                                                 tr("Archivos de texto plano"));

    if(nombreArchivo != ""){
        QFile archivo;
        archivo.setFileName(nombreArchivo);
        if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
            archivo.write(txtEditor_->toPlainText().toUtf8());
            archivo.close();
        }
    }
}


void NotepadWindow::alFuente()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, txtEditor_->font(), this);
    if (ok) {
        // Si el usuario hizo click en OK, se establece la fuente seleccionada
        txtEditor_->setFont(font);
    }
}

void NotepadWindow::alAyuda()
{
     QMessageBox::information(this, "Ayuda", "Ayuda del programa");
}
