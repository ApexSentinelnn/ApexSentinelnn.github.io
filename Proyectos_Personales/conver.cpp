#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QImage>
#include <QPixmap>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QComboBox>
#include <QSpinBox>
#include <QImageWriter>

class ImageConverter : public QMainWindow {
    Q_OBJECT

private:
    QLabel *imageLabel;
    QString currentImagePath;
    QComboBox *formatComboBox;
    QSpinBox *widthSpinBox, *heightSpinBox;

public:
    ImageConverter(QWidget *parent = nullptr) : QMainWindow(parent) {
        setAcceptDrops(true);
        setWindowTitle("Conversor de Imágenes");
        resize(400, 300);

        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(centralWidget);

        imageLabel = new QLabel("Arrastra una imagen aquí", this);
        imageLabel->setAlignment(Qt::AlignCenter);
        imageLabel->setStyleSheet("border: 2px dashed gray;");
        layout->addWidget(imageLabel);

        formatComboBox = new QComboBox(this);
        formatComboBox->addItems({"png", "jpg", "webp", "ico"});
        layout->addWidget(formatComboBox);

        widthSpinBox = new QSpinBox(this);
        widthSpinBox->setRange(10, 5000);
        widthSpinBox->setValue(400);
        layout->addWidget(widthSpinBox);

        heightSpinBox = new QSpinBox(this);
        heightSpinBox->setRange(10, 5000);
        heightSpinBox->setValue(300);
        layout->addWidget(heightSpinBox);

        QPushButton *convertButton = new QPushButton("Convertir", this);
        layout->addWidget(convertButton);

        connect(convertButton, &QPushButton::clicked, this, &ImageConverter::convertImage);
        setCentralWidget(centralWidget);
    }

protected:
    void dragEnterEvent(QDragEnterEvent *event) override {
        if (event->mimeData()->hasUrls()) {
            event->acceptProposedAction();
        }
    }

    void dropEvent(QDropEvent *event) override {
        QList<QUrl> urls = event->mimeData()->urls();
        if (!urls.isEmpty()) {
            currentImagePath = urls.first().toLocalFile();
            QPixmap pixmap(currentImagePath);
            imageLabel->setPixmap(pixmap.scaled(200, 200, Qt::KeepAspectRatio));
        }
    }

private slots:
    void convertImage() {
        if (currentImagePath.isEmpty()) return;

        QImage image(currentImagePath);
        int newWidth = widthSpinBox->value();
        int newHeight = heightSpinBox->value();
        QImage scaledImage = image.scaled(newWidth, newHeight, Qt::KeepAspectRatio);

        QString newFormat = formatComboBox->currentText();
        QString newPath = QFileDialog::getSaveFileName(this, "Guardar imagen", "", "*." + newFormat);
        if (!newPath.isEmpty()) {
            scaledImage.save(newPath);
        }
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ImageConverter window;
    window.show();
    return app.exec();
}
