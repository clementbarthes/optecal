/********************************************************************************
** Form generated from reading UI file 'optecal.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTECAL_H
#define UI_OPTECAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qlabelwmouse.h"

QT_BEGIN_NAMESPACE

class Ui_OpteCAL
{
public:
    QAction *actionNew_Project;
    QAction *actionLoad_Project;
    QAction *actionSave_Project;
    QAction *actionSave_Project_as;
    QAction *actionLoad_calibration_images;
    QAction *actionLoad_RAW_files;
    QAction *actionLoad_experiment_images;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_42;
    QHBoxLayout *horizontalLayout_10;
    QToolBox *loadFilesToolBox;
    QWidget *rawConverterPage;
    QVBoxLayout *verticalLayout_17;
    QVBoxLayout *verticalLayout_16;
    QPushButton *loadRawImage;
    QLabel *labelRaw;
    QListWidget *rawFilesWidget;
    QComboBox *sortRawFilesComboBox;
    QWidget *page_5;
    QVBoxLayout *verticalLayout_18;
    QVBoxLayout *verticalLayout_2;
    QPushButton *loadImageCal;
    QLabel *label_2;
    QListWidget *listFilesCalWidget;
    QComboBox *sortFilesCalComboBox;
    QWidget *page_6;
    QVBoxLayout *verticalLayout_28;
    QVBoxLayout *verticalLayout;
    QPushButton *loadImage;
    QLabel *label;
    QListWidget *listFilesWidget;
    QComboBox *sortFilesComboBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_14;
    QLabel *frameRateLabel;
    QDoubleSpinBox *frameRateSpinBox;
    QLabel *fpsLabel;
    QPushButton *pauseButton;
    QPushButton *playButton;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_9;
    QLabelWMouse *currentImgDisplay;
    QLabelWMouse *scaleLabel;
    QVBoxLayout *rawConverterLayout;
    QSpacerItem *verticalSpacer_5;
    QLabel *logoLabel;
    QSpacerItem *verticalSpacer_6;
    QGroupBox *calibrationGroupBox;
    QVBoxLayout *verticalLayout_64;
    QVBoxLayout *verticalLayout_63;
    QCheckBox *enableCalibrationCheck;
    QVBoxLayout *verticalLayout_59;
    QGroupBox *groupBox_14;
    QVBoxLayout *verticalLayout_57;
    QVBoxLayout *verticalLayout_55;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_12;
    QComboBox *makerCombo;
    QHBoxLayout *horizontalLayout_42;
    QLabel *label_13;
    QComboBox *modelCombo;
    QHBoxLayout *horizontalLayout_46;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_17;
    QLineEdit *cropFactorEdit;
    QGroupBox *groupBox_15;
    QVBoxLayout *verticalLayout_61;
    QVBoxLayout *verticalLayout_58;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_15;
    QComboBox *lensMakerCombo;
    QHBoxLayout *horizontalLayout_43;
    QLabel *label_14;
    QComboBox *lensCombo;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_16;
    QComboBox *focalLengthCombo;
    QHBoxLayout *horizontalLayout_47;
    QLabel *label_18;
    QLineEdit *aEdit;
    QLabel *label_19;
    QLineEdit *bEdit;
    QLabel *label_20;
    QLineEdit *cEdit;
    QGroupBox *rawGroupBox;
    QVBoxLayout *verticalLayout_40;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *turnCCWButton;
    QPushButton *turnCWButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_48;
    QSpacerItem *horizontalSpacer_24;
    QPushButton *convertSelectedButton;
    QSpacerItem *horizontalSpacer_23;
    QHBoxLayout *horizontalLayout_49;
    QSpacerItem *horizontalSpacer_25;
    QPushButton *convertAllButton;
    QSpacerItem *horizontalSpacer_26;
    QToolBox *modulesToolBox;
    QWidget *calibration;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_4;
    QSpinBox *heightSpinBox;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_3;
    QSpinBox *widthSpinBox;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_33;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *findCornersButton;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *calibratePushButton;
    QWidget *drawRoi;
    QVBoxLayout *verticalLayout_31;
    QVBoxLayout *verticalLayout_30;
    QGroupBox *roiGroupBox;
    QVBoxLayout *verticalLayout_29;
    QHBoxLayout *horizontalLayout_29;
    QPushButton *plusPolyButton;
    QPushButton *minusPolyButton;
    QSpacerItem *horizontalSpacer_15;
    QHBoxLayout *horizontalLayout_30;
    QPushButton *plusCircleButton;
    QPushButton *minusCircleButton;
    QSpacerItem *horizontalSpacer_17;
    QGroupBox *lengthCalibrateGroupBox;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *pixelLineEdit;
    QLabel *pixelsLabel;
    QLabel *equalLabel;
    QLineEdit *unitLineEdit;
    QComboBox *unitComboBox;
    QPushButton *applyScaleButton;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *measureButton;
    QLabel *pixelEURatioLabel;
    QSpacerItem *verticalSpacer_3;
    QWidget *runAnalysis;
    QVBoxLayout *verticalLayout_20;
    QVBoxLayout *verticalLayout_19;
    QPushButton *setSeedButton;
    QGroupBox *correlationParamsBox;
    QVBoxLayout *verticalLayout_22;
    QVBoxLayout *verticalLayout_21;
    QHBoxLayout *horizontalLayout_19;
    QLabel *subsetSizeLabel;
    QLineEdit *subsetSizeText;
    QLabel *label_5;
    QSlider *subsetSizeSlider;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_20;
    QLabel *subsetSpacingLabel;
    QLineEdit *subsetSpacingText;
    QLabel *label_6;
    QSlider *subsetSpacingSlider;
    QHBoxLayout *horizontalLayout_18;
    QLabel *splineLabel;
    QComboBox *splineComboBox;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_17;
    QLabel *researchLabel;
    QSpinBox *searchRegionSpinBox;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QLineEdit *corrRejectionLineEdit;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_21;
    QPushButton *analyzeCurrentFrameButton;
    QPushButton *analyseAllFramesButton;
    QSpacerItem *horizontalSpacer_8;
    QCheckBox *highStrainCheckBox;
    QCheckBox *guiResponsiveCheckBox;
    QSpacerItem *verticalSpacer_2;
    QWidget *resultsDisplay;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *dispComboBox;
    QComboBox *unitsDisplayComboBox;
    QComboBox *scaleComboBox;
    QGroupBox *amplifiedMotionBox;
    QVBoxLayout *verticalLayout_66;
    QVBoxLayout *verticalLayout_65;
    QHBoxLayout *horizontalLayout_40;
    QLabel *label_9;
    QSlider *amplificationSlider;
    QLineEdit *amplificationEdit;
    QLabel *ampPercent;
    QHBoxLayout *horizontalLayout_39;
    QLabel *label_21;
    QSlider *backgroundSlider;
    QLineEdit *backgroundEdit;
    QLabel *ampPercent_2;
    QGroupBox *limitGroupBox;
    QVBoxLayout *verticalLayout_54;
    QVBoxLayout *verticalLayout_53;
    QLabel *lowerBoundLabel;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox_11;
    QVBoxLayout *verticalLayout_11;
    QLineEdit *lowerBoundText;
    QVBoxLayout *verticalLayout_10;
    QSlider *lowerBoundSlider;
    QSlider *upperBoundSlider;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_56;
    QLineEdit *upperBoundText;
    QLabel *upperBoundLabel;
    QHBoxLayout *horizontalLayout_9;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout_52;
    QSlider *colormapSlider;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *correlClippingGroupBox;
    QVBoxLayout *verticalLayout_41;
    QHBoxLayout *horizontalLayout_3;
    QSlider *correlClipSlider;
    QGroupBox *groupBox_9;
    QVBoxLayout *verticalLayout_51;
    QHBoxLayout *horizontalLayout_41;
    QLineEdit *clippingValText;
    QLabel *label_11;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_39;
    QVBoxLayout *verticalLayout_38;
    QHBoxLayout *horizontalLayout_32;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_35;
    QVBoxLayout *verticalLayout_34;
    QRadioButton *referenceRadio;
    QRadioButton *deformedRadio;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_37;
    QVBoxLayout *verticalLayout_36;
    QRadioButton *greenLagrangeRadio;
    QRadioButton *greenAlmansiRadio;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *showAxesCheckBox;
    QCheckBox *flipXYCheckBox;
    QComboBox *cartesianPolarComboBox;
    QGroupBox *filtersGroupBox;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *filterLabel;
    QSlider *filterSlider;
    QVBoxLayout *verticalLayout_5;
    QLabel *gaussianFilterLabel;
    QSlider *gaussianFilterSlider;
    QWidget *page;
    QVBoxLayout *verticalLayout_62;
    QVBoxLayout *verticalLayout_60;
    QGroupBox *SGGroupBox;
    QVBoxLayout *verticalLayout_32;
    QHBoxLayout *horizontalLayout_36;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_34;
    QPushButton *addStrainGaugeButton;
    QSpacerItem *horizontalSpacer_18;
    QListWidget *virtualStrainGaugeList;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_48;
    QVBoxLayout *verticalLayout_47;
    QLabel *sgWidthLabel;
    QLabel *sgOriginLabel;
    QLabel *sgHeightLabel;
    QLabel *sgAngleLabel;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_44;
    QVBoxLayout *verticalLayout_43;
    QLabel *e11Label;
    QLabel *e22Label;
    QLabel *e12Label;
    QGroupBox *extensometerGroupBox;
    QVBoxLayout *verticalLayout_33;
    QHBoxLayout *horizontalLayout_37;
    QVBoxLayout *verticalLayout_23;
    QHBoxLayout *horizontalLayout_35;
    QPushButton *addExtensometerButton;
    QSpacerItem *horizontalSpacer_19;
    QListWidget *extensometerList;
    QVBoxLayout *verticalLayout_24;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_50;
    QVBoxLayout *verticalLayout_49;
    QLabel *extPointsLabel;
    QLabel *extLengthLabel;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_46;
    QVBoxLayout *verticalLayout_45;
    QLabel *elongationLabel;
    QLabel *elongationXLabel;
    QLabel *elongationYLabel;
    QHBoxLayout *horizontalLayout_38;
    QSpacerItem *horizontalSpacer_22;
    QPushButton *ppExportButton;
    QWidget *exportTools;
    QVBoxLayout *verticalLayout_27;
    QVBoxLayout *verticalLayout_25;
    QHBoxLayout *horizontalLayout_22;
    QSplitter *splitter_2;
    QCheckBox *xCheck;
    QCheckBox *yCheck;
    QCheckBox *rotationCheck;
    QCheckBox *pStrain1Check;
    QCheckBox *pStrain2Check;
    QCheckBox *pDirection1Check;
    QCheckBox *pDirection2Check;
    QCheckBox *corrCoefCheck;
    QSplitter *splitter;
    QCheckBox *uCheck;
    QCheckBox *vCheck;
    QCheckBox *exxCheck;
    QCheckBox *eyyCheck;
    QCheckBox *exyCheck;
    QCheckBox *TrescaStrainCheck;
    QCheckBox *vmStrainCheck;
    QSpacerItem *horizontalSpacer_13;
    QHBoxLayout *horizontalLayout_23;
    QComboBox *exportTypeComboBox;
    QPushButton *exportCurrentButton;
    QHBoxLayout *horizontalLayout_24;
    QSpacerItem *horizontalSpacer_12;
    QPushButton *exportAllButton;
    QGroupBox *videoGroupBox;
    QHBoxLayout *horizontalLayout_28;
    QHBoxLayout *horizontalLayout_27;
    QVBoxLayout *verticalLayout_26;
    QHBoxLayout *horizontalLayout_25;
    QLabel *frameRateLabel_2;
    QDoubleSpinBox *exportFrameRateSpinBox;
    QLabel *fpsLabel_2;
    QHBoxLayout *horizontalLayout_26;
    QLabel *videoFormatLabel;
    QComboBox *videoTypeComboBox;
    QSpacerItem *horizontalSpacer_16;
    QPushButton *videoExportButton;
    QSpacerItem *verticalSpacer_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OpteCAL)
    {
        if (OpteCAL->objectName().isEmpty())
            OpteCAL->setObjectName("OpteCAL");
        OpteCAL->resize(1232, 825);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OpteCAL->sizePolicy().hasHeightForWidth());
        OpteCAL->setSizePolicy(sizePolicy);
        OpteCAL->setMinimumSize(QSize(0, 0));
        OpteCAL->setBaseSize(QSize(750, 600));
        actionNew_Project = new QAction(OpteCAL);
        actionNew_Project->setObjectName("actionNew_Project");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/1413506373_txt.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Project->setIcon(icon);
        actionLoad_Project = new QAction(OpteCAL);
        actionLoad_Project->setObjectName("actionLoad_Project");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/resources/1413506500_folderopen1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad_Project->setIcon(icon1);
        actionSave_Project = new QAction(OpteCAL);
        actionSave_Project->setObjectName("actionSave_Project");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/resources/1413506336_3floppy_unmount.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Project->setIcon(icon2);
        actionSave_Project_as = new QAction(OpteCAL);
        actionSave_Project_as->setObjectName("actionSave_Project_as");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/resources/1413506309_filesaveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Project_as->setIcon(icon3);
        actionLoad_calibration_images = new QAction(OpteCAL);
        actionLoad_calibration_images->setObjectName("actionLoad_calibration_images");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/resources/loadImagesRuler.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad_calibration_images->setIcon(icon4);
        actionLoad_RAW_files = new QAction(OpteCAL);
        actionLoad_RAW_files->setObjectName("actionLoad_RAW_files");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/resources/loadRawImages.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad_RAW_files->setIcon(icon5);
        actionLoad_experiment_images = new QAction(OpteCAL);
        actionLoad_experiment_images->setObjectName("actionLoad_experiment_images");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/resources/loadImagesCoupon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad_experiment_images->setIcon(icon6);
        centralWidget = new QWidget(OpteCAL);
        centralWidget->setObjectName("centralWidget");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setMinimumSize(QSize(0, 0));
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_42 = new QVBoxLayout(centralWidget);
        verticalLayout_42->setSpacing(6);
        verticalLayout_42->setContentsMargins(11, 11, 11, 11);
        verticalLayout_42->setObjectName("verticalLayout_42");
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        loadFilesToolBox = new QToolBox(centralWidget);
        loadFilesToolBox->setObjectName("loadFilesToolBox");
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(loadFilesToolBox->sizePolicy().hasHeightForWidth());
        loadFilesToolBox->setSizePolicy(sizePolicy2);
        loadFilesToolBox->setMinimumSize(QSize(240, 0));
        QFont font;
        font.setPointSize(10);
        loadFilesToolBox->setFont(font);
        loadFilesToolBox->setStyleSheet(QString::fromUtf8(""));
        loadFilesToolBox->setFrameShape(QFrame::StyledPanel);
        loadFilesToolBox->setLineWidth(1);
        loadFilesToolBox->setMidLineWidth(3);
        rawConverterPage = new QWidget();
        rawConverterPage->setObjectName("rawConverterPage");
        rawConverterPage->setGeometry(QRect(0, 0, 244, 591));
        verticalLayout_17 = new QVBoxLayout(rawConverterPage);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName("verticalLayout_17");
        verticalLayout_16 = new QVBoxLayout();
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setObjectName("verticalLayout_16");
        loadRawImage = new QPushButton(rawConverterPage);
        loadRawImage->setObjectName("loadRawImage");
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(loadRawImage->sizePolicy().hasHeightForWidth());
        loadRawImage->setSizePolicy(sizePolicy3);
        loadRawImage->setIcon(icon5);
        loadRawImage->setIconSize(QSize(40, 40));

        verticalLayout_16->addWidget(loadRawImage);

        labelRaw = new QLabel(rawConverterPage);
        labelRaw->setObjectName("labelRaw");
        labelRaw->setFont(font);

        verticalLayout_16->addWidget(labelRaw);

        rawFilesWidget = new QListWidget(rawConverterPage);
        rawFilesWidget->setObjectName("rawFilesWidget");
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(rawFilesWidget->sizePolicy().hasHeightForWidth());
        rawFilesWidget->setSizePolicy(sizePolicy4);
        rawFilesWidget->setMinimumSize(QSize(220, 0));
        rawFilesWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        rawFilesWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout_16->addWidget(rawFilesWidget);

        sortRawFilesComboBox = new QComboBox(rawConverterPage);
        sortRawFilesComboBox->addItem(QString());
        sortRawFilesComboBox->addItem(QString());
        sortRawFilesComboBox->addItem(QString());
        sortRawFilesComboBox->setObjectName("sortRawFilesComboBox");
        sizePolicy3.setHeightForWidth(sortRawFilesComboBox->sizePolicy().hasHeightForWidth());
        sortRawFilesComboBox->setSizePolicy(sizePolicy3);

        verticalLayout_16->addWidget(sortRawFilesComboBox);


        verticalLayout_17->addLayout(verticalLayout_16);

        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/resources/1415596481_Pictures.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadFilesToolBox->addItem(rawConverterPage, icon7, QString::fromUtf8("Convert Raw images"));
        page_5 = new QWidget();
        page_5->setObjectName("page_5");
        page_5->setGeometry(QRect(0, 0, 258, 591));
        verticalLayout_18 = new QVBoxLayout(page_5);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName("verticalLayout_18");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        loadImageCal = new QPushButton(page_5);
        loadImageCal->setObjectName("loadImageCal");
        sizePolicy3.setHeightForWidth(loadImageCal->sizePolicy().hasHeightForWidth());
        loadImageCal->setSizePolicy(sizePolicy3);
        loadImageCal->setIcon(icon4);
        loadImageCal->setIconSize(QSize(40, 40));

        verticalLayout_2->addWidget(loadImageCal);

        label_2 = new QLabel(page_5);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);

        listFilesCalWidget = new QListWidget(page_5);
        listFilesCalWidget->setObjectName("listFilesCalWidget");
        sizePolicy4.setHeightForWidth(listFilesCalWidget->sizePolicy().hasHeightForWidth());
        listFilesCalWidget->setSizePolicy(sizePolicy4);
        listFilesCalWidget->setMinimumSize(QSize(220, 0));
        listFilesCalWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        listFilesCalWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout_2->addWidget(listFilesCalWidget);

        sortFilesCalComboBox = new QComboBox(page_5);
        sortFilesCalComboBox->addItem(QString());
        sortFilesCalComboBox->addItem(QString());
        sortFilesCalComboBox->addItem(QString());
        sortFilesCalComboBox->setObjectName("sortFilesCalComboBox");
        sizePolicy3.setHeightForWidth(sortFilesCalComboBox->sizePolicy().hasHeightForWidth());
        sortFilesCalComboBox->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(sortFilesCalComboBox);


        verticalLayout_18->addLayout(verticalLayout_2);

        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/resources/1415596851_Project.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadFilesToolBox->addItem(page_5, icon8, QString::fromUtf8("Calibration images"));
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        page_6->setGeometry(QRect(0, 0, 337, 591));
        verticalLayout_28 = new QVBoxLayout(page_6);
        verticalLayout_28->setSpacing(6);
        verticalLayout_28->setContentsMargins(11, 11, 11, 11);
        verticalLayout_28->setObjectName("verticalLayout_28");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        loadImage = new QPushButton(page_6);
        loadImage->setObjectName("loadImage");
        sizePolicy3.setHeightForWidth(loadImage->sizePolicy().hasHeightForWidth());
        loadImage->setSizePolicy(sizePolicy3);
        loadImage->setIcon(icon6);
        loadImage->setIconSize(QSize(40, 40));

        verticalLayout->addWidget(loadImage);

        label = new QLabel(page_6);
        label->setObjectName("label");
        label->setFont(font);

        verticalLayout->addWidget(label);

        listFilesWidget = new QListWidget(page_6);
        listFilesWidget->setObjectName("listFilesWidget");
        sizePolicy4.setHeightForWidth(listFilesWidget->sizePolicy().hasHeightForWidth());
        listFilesWidget->setSizePolicy(sizePolicy4);
        listFilesWidget->setMinimumSize(QSize(220, 0));
        listFilesWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        listFilesWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);

        verticalLayout->addWidget(listFilesWidget);

        sortFilesComboBox = new QComboBox(page_6);
        sortFilesComboBox->addItem(QString());
        sortFilesComboBox->addItem(QString());
        sortFilesComboBox->addItem(QString());
        sortFilesComboBox->setObjectName("sortFilesComboBox");
        sizePolicy3.setHeightForWidth(sortFilesComboBox->sizePolicy().hasHeightForWidth());
        sortFilesComboBox->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(sortFilesComboBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_14);

        frameRateLabel = new QLabel(page_6);
        frameRateLabel->setObjectName("frameRateLabel");

        horizontalLayout->addWidget(frameRateLabel);

        frameRateSpinBox = new QDoubleSpinBox(page_6);
        frameRateSpinBox->setObjectName("frameRateSpinBox");
        frameRateSpinBox->setDecimals(1);
        frameRateSpinBox->setMinimum(0.100000000000000);
        frameRateSpinBox->setMaximum(10.000000000000000);
        frameRateSpinBox->setValue(2.000000000000000);

        horizontalLayout->addWidget(frameRateSpinBox);

        fpsLabel = new QLabel(page_6);
        fpsLabel->setObjectName("fpsLabel");

        horizontalLayout->addWidget(fpsLabel);

        pauseButton = new QPushButton(page_6);
        pauseButton->setObjectName("pauseButton");
        sizePolicy3.setHeightForWidth(pauseButton->sizePolicy().hasHeightForWidth());
        pauseButton->setSizePolicy(sizePolicy3);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/resources/1413496681_Pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        pauseButton->setIcon(icon9);

        horizontalLayout->addWidget(pauseButton);

        playButton = new QPushButton(page_6);
        playButton->setObjectName("playButton");
        sizePolicy3.setHeightForWidth(playButton->sizePolicy().hasHeightForWidth());
        playButton->setSizePolicy(sizePolicy3);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/resources/1413496671_Play.png"), QSize(), QIcon::Normal, QIcon::Off);
        playButton->setIcon(icon10);

        horizontalLayout->addWidget(playButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_28->addLayout(verticalLayout);

        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/resources/coupon_cropped.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadFilesToolBox->addItem(page_6, icon11, QString::fromUtf8("Experiment images"));

        horizontalLayout_10->addWidget(loadFilesToolBox);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName("scrollArea");
        QSizePolicy sizePolicy5(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy5);
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 210, 704));
        verticalLayout_9 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName("verticalLayout_9");
        currentImgDisplay = new QLabelWMouse(scrollAreaWidgetContents_2);
        currentImgDisplay->setObjectName("currentImgDisplay");
        sizePolicy3.setHeightForWidth(currentImgDisplay->sizePolicy().hasHeightForWidth());
        currentImgDisplay->setSizePolicy(sizePolicy3);
        currentImgDisplay->setMinimumSize(QSize(0, 300));
        currentImgDisplay->setSizeIncrement(QSize(150, 150));
        currentImgDisplay->setMouseTracking(true);
        currentImgDisplay->setFrameShape(QFrame::NoFrame);
        currentImgDisplay->setLineWidth(1);
        currentImgDisplay->setAlignment(Qt::AlignCenter);
        currentImgDisplay->setMargin(0);

        verticalLayout_9->addWidget(currentImgDisplay);

        scrollArea->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout_10->addWidget(scrollArea);

        scaleLabel = new QLabelWMouse(centralWidget);
        scaleLabel->setObjectName("scaleLabel");
        QSizePolicy sizePolicy6(QSizePolicy::Maximum, QSizePolicy::Ignored);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(scaleLabel->sizePolicy().hasHeightForWidth());
        scaleLabel->setSizePolicy(sizePolicy6);

        horizontalLayout_10->addWidget(scaleLabel);

        rawConverterLayout = new QVBoxLayout();
        rawConverterLayout->setSpacing(6);
        rawConverterLayout->setObjectName("rawConverterLayout");
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        rawConverterLayout->addItem(verticalSpacer_5);

        logoLabel = new QLabel(centralWidget);
        logoLabel->setObjectName("logoLabel");
        logoLabel->setScaledContents(false);

        rawConverterLayout->addWidget(logoLabel);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        rawConverterLayout->addItem(verticalSpacer_6);

        calibrationGroupBox = new QGroupBox(centralWidget);
        calibrationGroupBox->setObjectName("calibrationGroupBox");
        sizePolicy.setHeightForWidth(calibrationGroupBox->sizePolicy().hasHeightForWidth());
        calibrationGroupBox->setSizePolicy(sizePolicy);
        calibrationGroupBox->setMinimumSize(QSize(300, 0));
        calibrationGroupBox->setMaximumSize(QSize(350, 16777215));
        verticalLayout_64 = new QVBoxLayout(calibrationGroupBox);
        verticalLayout_64->setSpacing(6);
        verticalLayout_64->setContentsMargins(11, 11, 11, 11);
        verticalLayout_64->setObjectName("verticalLayout_64");
        verticalLayout_63 = new QVBoxLayout();
        verticalLayout_63->setSpacing(6);
        verticalLayout_63->setObjectName("verticalLayout_63");
        enableCalibrationCheck = new QCheckBox(calibrationGroupBox);
        enableCalibrationCheck->setObjectName("enableCalibrationCheck");

        verticalLayout_63->addWidget(enableCalibrationCheck);

        verticalLayout_59 = new QVBoxLayout();
        verticalLayout_59->setSpacing(6);
        verticalLayout_59->setObjectName("verticalLayout_59");
        groupBox_14 = new QGroupBox(calibrationGroupBox);
        groupBox_14->setObjectName("groupBox_14");
        verticalLayout_57 = new QVBoxLayout(groupBox_14);
        verticalLayout_57->setSpacing(6);
        verticalLayout_57->setContentsMargins(11, 11, 11, 11);
        verticalLayout_57->setObjectName("verticalLayout_57");
        verticalLayout_55 = new QVBoxLayout();
        verticalLayout_55->setSpacing(6);
        verticalLayout_55->setObjectName("verticalLayout_55");
        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setObjectName("horizontalLayout_31");
        label_12 = new QLabel(groupBox_14);
        label_12->setObjectName("label_12");
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_31->addWidget(label_12);

        makerCombo = new QComboBox(groupBox_14);
        makerCombo->setObjectName("makerCombo");

        horizontalLayout_31->addWidget(makerCombo);


        verticalLayout_55->addLayout(horizontalLayout_31);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setSpacing(6);
        horizontalLayout_42->setObjectName("horizontalLayout_42");
        label_13 = new QLabel(groupBox_14);
        label_13->setObjectName("label_13");
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_42->addWidget(label_13);

        modelCombo = new QComboBox(groupBox_14);
        modelCombo->setObjectName("modelCombo");

        horizontalLayout_42->addWidget(modelCombo);


        verticalLayout_55->addLayout(horizontalLayout_42);

        horizontalLayout_46 = new QHBoxLayout();
        horizontalLayout_46->setSpacing(6);
        horizontalLayout_46->setObjectName("horizontalLayout_46");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_46->addItem(horizontalSpacer_3);

        label_17 = new QLabel(groupBox_14);
        label_17->setObjectName("label_17");
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_46->addWidget(label_17);

        cropFactorEdit = new QLineEdit(groupBox_14);
        cropFactorEdit->setObjectName("cropFactorEdit");
        QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(cropFactorEdit->sizePolicy().hasHeightForWidth());
        cropFactorEdit->setSizePolicy(sizePolicy7);

        horizontalLayout_46->addWidget(cropFactorEdit);


        verticalLayout_55->addLayout(horizontalLayout_46);


        verticalLayout_57->addLayout(verticalLayout_55);


        verticalLayout_59->addWidget(groupBox_14);

        groupBox_15 = new QGroupBox(calibrationGroupBox);
        groupBox_15->setObjectName("groupBox_15");
        verticalLayout_61 = new QVBoxLayout(groupBox_15);
        verticalLayout_61->setSpacing(6);
        verticalLayout_61->setContentsMargins(11, 11, 11, 11);
        verticalLayout_61->setObjectName("verticalLayout_61");
        verticalLayout_58 = new QVBoxLayout();
        verticalLayout_58->setSpacing(6);
        verticalLayout_58->setObjectName("verticalLayout_58");
        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setSpacing(6);
        horizontalLayout_44->setObjectName("horizontalLayout_44");
        label_15 = new QLabel(groupBox_15);
        label_15->setObjectName("label_15");
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_44->addWidget(label_15);

        lensMakerCombo = new QComboBox(groupBox_15);
        lensMakerCombo->setObjectName("lensMakerCombo");

        horizontalLayout_44->addWidget(lensMakerCombo);


        verticalLayout_58->addLayout(horizontalLayout_44);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setSpacing(6);
        horizontalLayout_43->setObjectName("horizontalLayout_43");
        label_14 = new QLabel(groupBox_15);
        label_14->setObjectName("label_14");
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_43->addWidget(label_14);

        lensCombo = new QComboBox(groupBox_15);
        lensCombo->setObjectName("lensCombo");
        lensCombo->setMinimumSize(QSize(0, 0));
        lensCombo->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        lensCombo->setMinimumContentsLength(0);

        horizontalLayout_43->addWidget(lensCombo);


        verticalLayout_58->addLayout(horizontalLayout_43);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setSpacing(6);
        horizontalLayout_45->setObjectName("horizontalLayout_45");
        label_16 = new QLabel(groupBox_15);
        label_16->setObjectName("label_16");
        label_16->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_45->addWidget(label_16);

        focalLengthCombo = new QComboBox(groupBox_15);
        focalLengthCombo->setObjectName("focalLengthCombo");

        horizontalLayout_45->addWidget(focalLengthCombo);


        verticalLayout_58->addLayout(horizontalLayout_45);

        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setSpacing(6);
        horizontalLayout_47->setObjectName("horizontalLayout_47");
        label_18 = new QLabel(groupBox_15);
        label_18->setObjectName("label_18");
        label_18->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_47->addWidget(label_18);

        aEdit = new QLineEdit(groupBox_15);
        aEdit->setObjectName("aEdit");
        sizePolicy7.setHeightForWidth(aEdit->sizePolicy().hasHeightForWidth());
        aEdit->setSizePolicy(sizePolicy7);

        horizontalLayout_47->addWidget(aEdit);

        label_19 = new QLabel(groupBox_15);
        label_19->setObjectName("label_19");
        label_19->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_47->addWidget(label_19);

        bEdit = new QLineEdit(groupBox_15);
        bEdit->setObjectName("bEdit");
        sizePolicy7.setHeightForWidth(bEdit->sizePolicy().hasHeightForWidth());
        bEdit->setSizePolicy(sizePolicy7);

        horizontalLayout_47->addWidget(bEdit);

        label_20 = new QLabel(groupBox_15);
        label_20->setObjectName("label_20");
        label_20->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_47->addWidget(label_20);

        cEdit = new QLineEdit(groupBox_15);
        cEdit->setObjectName("cEdit");
        sizePolicy7.setHeightForWidth(cEdit->sizePolicy().hasHeightForWidth());
        cEdit->setSizePolicy(sizePolicy7);

        horizontalLayout_47->addWidget(cEdit);


        verticalLayout_58->addLayout(horizontalLayout_47);


        verticalLayout_61->addLayout(verticalLayout_58);


        verticalLayout_59->addWidget(groupBox_15);


        verticalLayout_63->addLayout(verticalLayout_59);


        verticalLayout_64->addLayout(verticalLayout_63);


        rawConverterLayout->addWidget(calibrationGroupBox);

        rawGroupBox = new QGroupBox(centralWidget);
        rawGroupBox->setObjectName("rawGroupBox");
        QSizePolicy sizePolicy8(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(rawGroupBox->sizePolicy().hasHeightForWidth());
        rawGroupBox->setSizePolicy(sizePolicy8);
        rawGroupBox->setMinimumSize(QSize(300, 0));
        rawGroupBox->setMaximumSize(QSize(350, 16777215));
        verticalLayout_40 = new QVBoxLayout(rawGroupBox);
        verticalLayout_40->setSpacing(6);
        verticalLayout_40->setContentsMargins(11, 11, 11, 11);
        verticalLayout_40->setObjectName("verticalLayout_40");
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName("verticalLayout_12");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        turnCCWButton = new QPushButton(rawGroupBox);
        turnCCWButton->setObjectName("turnCCWButton");
        sizePolicy3.setHeightForWidth(turnCCWButton->sizePolicy().hasHeightForWidth());
        turnCCWButton->setSizePolicy(sizePolicy3);
        turnCCWButton->setMinimumSize(QSize(40, 40));
        turnCCWButton->setMaximumSize(QSize(40, 40));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/resources/1415592418_RotateCC.png"), QSize(), QIcon::Normal, QIcon::Off);
        turnCCWButton->setIcon(icon12);
        turnCCWButton->setIconSize(QSize(32, 32));

        horizontalLayout_2->addWidget(turnCCWButton);

        turnCWButton = new QPushButton(rawGroupBox);
        turnCWButton->setObjectName("turnCWButton");
        sizePolicy3.setHeightForWidth(turnCWButton->sizePolicy().hasHeightForWidth());
        turnCWButton->setSizePolicy(sizePolicy3);
        turnCWButton->setMinimumSize(QSize(40, 40));
        turnCWButton->setMaximumSize(QSize(40, 40));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/resources/1415592418_Rotate.png"), QSize(), QIcon::Normal, QIcon::Off);
        turnCWButton->setIcon(icon13);
        turnCWButton->setIconSize(QSize(32, 32));

        horizontalLayout_2->addWidget(turnCWButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_12->addLayout(horizontalLayout_2);

        horizontalLayout_48 = new QHBoxLayout();
        horizontalLayout_48->setSpacing(6);
        horizontalLayout_48->setObjectName("horizontalLayout_48");
        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_48->addItem(horizontalSpacer_24);

        convertSelectedButton = new QPushButton(rawGroupBox);
        convertSelectedButton->setObjectName("convertSelectedButton");

        horizontalLayout_48->addWidget(convertSelectedButton);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_48->addItem(horizontalSpacer_23);


        verticalLayout_12->addLayout(horizontalLayout_48);

        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(6);
        horizontalLayout_49->setObjectName("horizontalLayout_49");
        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_49->addItem(horizontalSpacer_25);

        convertAllButton = new QPushButton(rawGroupBox);
        convertAllButton->setObjectName("convertAllButton");
        QFont font1;
        font1.setBold(true);
        convertAllButton->setFont(font1);

        horizontalLayout_49->addWidget(convertAllButton);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_49->addItem(horizontalSpacer_26);


        verticalLayout_12->addLayout(horizontalLayout_49);


        verticalLayout_40->addLayout(verticalLayout_12);


        rawConverterLayout->addWidget(rawGroupBox);


        horizontalLayout_10->addLayout(rawConverterLayout);

        modulesToolBox = new QToolBox(centralWidget);
        modulesToolBox->setObjectName("modulesToolBox");
        QSizePolicy sizePolicy9(QSizePolicy::Preferred, QSizePolicy::Ignored);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(modulesToolBox->sizePolicy().hasHeightForWidth());
        modulesToolBox->setSizePolicy(sizePolicy9);
        modulesToolBox->setMinimumSize(QSize(350, 365));
        modulesToolBox->setMaximumSize(QSize(250, 16777215));
        QPalette palette;
        QBrush brush(QColor(240, 240, 240, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        modulesToolBox->setPalette(palette);
        QFont font2;
        font2.setPointSize(8);
        modulesToolBox->setFont(font2);
        modulesToolBox->setFocusPolicy(Qt::TabFocus);
        modulesToolBox->setLayoutDirection(Qt::LeftToRight);
        modulesToolBox->setFrameShape(QFrame::StyledPanel);
        calibration = new QWidget();
        calibration->setObjectName("calibration");
        calibration->setGeometry(QRect(0, 0, 348, 504));
        groupBox = new QGroupBox(calibration);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 20, 321, 171));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 20, 229, 24));
        horizontalLayout_16 = new QHBoxLayout(layoutWidget);
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        horizontalLayout_16->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_11);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_16->addWidget(label_4);

        heightSpinBox = new QSpinBox(layoutWidget);
        heightSpinBox->setObjectName("heightSpinBox");
        heightSpinBox->setMinimum(3);
        heightSpinBox->setMaximum(20);
        heightSpinBox->setValue(8);

        horizontalLayout_16->addWidget(heightSpinBox);

        layoutWidget2 = new QWidget(groupBox);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(0, 40, 247, 24));
        horizontalLayout_15 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        horizontalLayout_15->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_10);

        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_15->addWidget(label_3);

        widthSpinBox = new QSpinBox(layoutWidget2);
        widthSpinBox->setObjectName("widthSpinBox");
        widthSpinBox->setMinimum(3);
        widthSpinBox->setMaximum(20);
        widthSpinBox->setValue(10);

        horizontalLayout_15->addWidget(widthSpinBox);

        layoutWidget3 = new QWidget(groupBox);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(30, 80, 208, 51));
        horizontalLayout_33 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_33->setSpacing(6);
        horizontalLayout_33->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_33->setObjectName("horizontalLayout_33");
        horizontalLayout_33->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_33->addItem(horizontalSpacer_7);

        findCornersButton = new QPushButton(layoutWidget3);
        findCornersButton->setObjectName("findCornersButton");
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/resources/checker.png"), QSize(), QIcon::Normal, QIcon::Off);
        findCornersButton->setIcon(icon14);
        findCornersButton->setIconSize(QSize(60, 40));

        horizontalLayout_33->addWidget(findCornersButton);

        layoutWidget4 = new QWidget(groupBox);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(100, 140, 123, 30));
        horizontalLayout_14 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_9);

        calibratePushButton = new QPushButton(layoutWidget4);
        calibratePushButton->setObjectName("calibratePushButton");

        horizontalLayout_14->addWidget(calibratePushButton);

        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/resources/1415619865_ruler.png"), QSize(), QIcon::Normal, QIcon::Off);
        modulesToolBox->addItem(calibration, icon15, QString::fromUtf8("Calibrate"));
        drawRoi = new QWidget();
        drawRoi->setObjectName("drawRoi");
        drawRoi->setGeometry(QRect(0, 0, 390, 487));
        verticalLayout_31 = new QVBoxLayout(drawRoi);
        verticalLayout_31->setSpacing(6);
        verticalLayout_31->setContentsMargins(11, 11, 11, 11);
        verticalLayout_31->setObjectName("verticalLayout_31");
        verticalLayout_30 = new QVBoxLayout();
        verticalLayout_30->setSpacing(6);
        verticalLayout_30->setObjectName("verticalLayout_30");
        roiGroupBox = new QGroupBox(drawRoi);
        roiGroupBox->setObjectName("roiGroupBox");
        verticalLayout_29 = new QVBoxLayout(roiGroupBox);
        verticalLayout_29->setSpacing(6);
        verticalLayout_29->setContentsMargins(11, 11, 11, 11);
        verticalLayout_29->setObjectName("verticalLayout_29");
        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName("horizontalLayout_29");
        plusPolyButton = new QPushButton(roiGroupBox);
        plusPolyButton->setObjectName("plusPolyButton");
        plusPolyButton->setEnabled(false);
        sizePolicy3.setHeightForWidth(plusPolyButton->sizePolicy().hasHeightForWidth());
        plusPolyButton->setSizePolicy(sizePolicy3);
        plusPolyButton->setMinimumSize(QSize(80, 62));
        plusPolyButton->setMaximumSize(QSize(80, 62));
        plusPolyButton->setBaseSize(QSize(100, 77));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/resources/plusPoly.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon16.addFile(QString::fromUtf8(":/resources/plusPolyDisabled.png"), QSize(), QIcon::Disabled, QIcon::Off);
        plusPolyButton->setIcon(icon16);
        plusPolyButton->setIconSize(QSize(80, 62));

        horizontalLayout_29->addWidget(plusPolyButton);

        minusPolyButton = new QPushButton(roiGroupBox);
        minusPolyButton->setObjectName("minusPolyButton");
        minusPolyButton->setEnabled(false);
        minusPolyButton->setMinimumSize(QSize(80, 62));
        minusPolyButton->setMaximumSize(QSize(80, 62));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/resources/minusPoly.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon17.addFile(QString::fromUtf8(":/resources/minusPolyDisabled.png"), QSize(), QIcon::Disabled, QIcon::Off);
        minusPolyButton->setIcon(icon17);
        minusPolyButton->setIconSize(QSize(80, 62));

        horizontalLayout_29->addWidget(minusPolyButton);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_29->addItem(horizontalSpacer_15);


        verticalLayout_29->addLayout(horizontalLayout_29);

        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setObjectName("horizontalLayout_30");
        plusCircleButton = new QPushButton(roiGroupBox);
        plusCircleButton->setObjectName("plusCircleButton");
        plusCircleButton->setEnabled(false);
        plusCircleButton->setMinimumSize(QSize(80, 62));
        plusCircleButton->setMaximumSize(QSize(80, 62));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/resources/plusCircle.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon18.addFile(QString::fromUtf8(":/resources/plusCircleDisabled.png"), QSize(), QIcon::Disabled, QIcon::Off);
        plusCircleButton->setIcon(icon18);
        plusCircleButton->setIconSize(QSize(80, 62));

        horizontalLayout_30->addWidget(plusCircleButton);

        minusCircleButton = new QPushButton(roiGroupBox);
        minusCircleButton->setObjectName("minusCircleButton");
        minusCircleButton->setEnabled(false);
        minusCircleButton->setMinimumSize(QSize(80, 62));
        minusCircleButton->setMaximumSize(QSize(80, 62));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/resources/minusCircle.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon19.addFile(QString::fromUtf8(":/resources/minusCircleDiabled.png"), QSize(), QIcon::Disabled, QIcon::Off);
        minusCircleButton->setIcon(icon19);
        minusCircleButton->setIconSize(QSize(80, 62));

        horizontalLayout_30->addWidget(minusCircleButton);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_30->addItem(horizontalSpacer_17);


        verticalLayout_29->addLayout(horizontalLayout_30);


        verticalLayout_30->addWidget(roiGroupBox);

        lengthCalibrateGroupBox = new QGroupBox(drawRoi);
        lengthCalibrateGroupBox->setObjectName("lengthCalibrateGroupBox");
        QSizePolicy sizePolicy10(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(lengthCalibrateGroupBox->sizePolicy().hasHeightForWidth());
        lengthCalibrateGroupBox->setSizePolicy(sizePolicy10);
        horizontalLayout_13 = new QHBoxLayout(lengthCalibrateGroupBox);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName("verticalLayout_13");
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pixelLineEdit = new QLineEdit(lengthCalibrateGroupBox);
        pixelLineEdit->setObjectName("pixelLineEdit");
        sizePolicy7.setHeightForWidth(pixelLineEdit->sizePolicy().hasHeightForWidth());
        pixelLineEdit->setSizePolicy(sizePolicy7);
        pixelLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(pixelLineEdit);

        pixelsLabel = new QLabel(lengthCalibrateGroupBox);
        pixelsLabel->setObjectName("pixelsLabel");

        horizontalLayout_4->addWidget(pixelsLabel);

        equalLabel = new QLabel(lengthCalibrateGroupBox);
        equalLabel->setObjectName("equalLabel");

        horizontalLayout_4->addWidget(equalLabel);

        unitLineEdit = new QLineEdit(lengthCalibrateGroupBox);
        unitLineEdit->setObjectName("unitLineEdit");
        sizePolicy7.setHeightForWidth(unitLineEdit->sizePolicy().hasHeightForWidth());
        unitLineEdit->setSizePolicy(sizePolicy7);
        unitLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(unitLineEdit);

        unitComboBox = new QComboBox(lengthCalibrateGroupBox);
        unitComboBox->addItem(QString());
        unitComboBox->addItem(QString());
        unitComboBox->addItem(QString());
        unitComboBox->addItem(QString());
        unitComboBox->addItem(QString());
        unitComboBox->setObjectName("unitComboBox");
        unitComboBox->setMaximumSize(QSize(60, 16777215));

        horizontalLayout_4->addWidget(unitComboBox);

        applyScaleButton = new QPushButton(lengthCalibrateGroupBox);
        applyScaleButton->setObjectName("applyScaleButton");
        sizePolicy7.setHeightForWidth(applyScaleButton->sizePolicy().hasHeightForWidth());
        applyScaleButton->setSizePolicy(sizePolicy7);
        applyScaleButton->setMaximumSize(QSize(75, 16777215));

        horizontalLayout_4->addWidget(applyScaleButton);


        verticalLayout_13->addLayout(horizontalLayout_4);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        measureButton = new QPushButton(lengthCalibrateGroupBox);
        measureButton->setObjectName("measureButton");
        measureButton->setEnabled(false);
        sizePolicy3.setHeightForWidth(measureButton->sizePolicy().hasHeightForWidth());
        measureButton->setSizePolicy(sizePolicy3);
        measureButton->setMinimumSize(QSize(130, 35));
        measureButton->setMaximumSize(QSize(16777215, 35));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/resources/ruler.png"), QSize(), QIcon::Normal, QIcon::Off);
        measureButton->setIcon(icon20);
        measureButton->setIconSize(QSize(30, 30));

        horizontalLayout_12->addWidget(measureButton);

        pixelEURatioLabel = new QLabel(lengthCalibrateGroupBox);
        pixelEURatioLabel->setObjectName("pixelEURatioLabel");

        horizontalLayout_12->addWidget(pixelEURatioLabel);


        verticalLayout_13->addLayout(horizontalLayout_12);


        horizontalLayout_13->addLayout(verticalLayout_13);


        verticalLayout_30->addWidget(lengthCalibrateGroupBox);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_30->addItem(verticalSpacer_3);


        verticalLayout_31->addLayout(verticalLayout_30);

        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/resources/1415619665_engineering.png"), QSize(), QIcon::Normal, QIcon::Off);
        modulesToolBox->addItem(drawRoi, icon21, QString::fromUtf8("Set up project properties"));
        runAnalysis = new QWidget();
        runAnalysis->setObjectName("runAnalysis");
        runAnalysis->setGeometry(QRect(0, 0, 383, 487));
        verticalLayout_20 = new QVBoxLayout(runAnalysis);
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setContentsMargins(11, 11, 11, 11);
        verticalLayout_20->setObjectName("verticalLayout_20");
        verticalLayout_19 = new QVBoxLayout();
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setObjectName("verticalLayout_19");
        setSeedButton = new QPushButton(runAnalysis);
        setSeedButton->setObjectName("setSeedButton");
        setSeedButton->setEnabled(true);
        sizePolicy3.setHeightForWidth(setSeedButton->sizePolicy().hasHeightForWidth());
        setSeedButton->setSizePolicy(sizePolicy3);
        setSeedButton->setMinimumSize(QSize(100, 35));
        setSeedButton->setMaximumSize(QSize(100, 30));
        QFont font3;
        font3.setPointSize(8);
        font3.setBold(true);
        setSeedButton->setFont(font3);
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/resources/1415540287_project-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        setSeedButton->setIcon(icon22);
        setSeedButton->setIconSize(QSize(30, 30));

        verticalLayout_19->addWidget(setSeedButton);

        correlationParamsBox = new QGroupBox(runAnalysis);
        correlationParamsBox->setObjectName("correlationParamsBox");
        sizePolicy2.setHeightForWidth(correlationParamsBox->sizePolicy().hasHeightForWidth());
        correlationParamsBox->setSizePolicy(sizePolicy2);
        correlationParamsBox->setMinimumSize(QSize(233, 0));
        verticalLayout_22 = new QVBoxLayout(correlationParamsBox);
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setContentsMargins(11, 11, 11, 11);
        verticalLayout_22->setObjectName("verticalLayout_22");
        verticalLayout_21 = new QVBoxLayout();
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setObjectName("verticalLayout_21");
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName("horizontalLayout_19");
        subsetSizeLabel = new QLabel(correlationParamsBox);
        subsetSizeLabel->setObjectName("subsetSizeLabel");
        sizePolicy3.setHeightForWidth(subsetSizeLabel->sizePolicy().hasHeightForWidth());
        subsetSizeLabel->setSizePolicy(sizePolicy3);
        subsetSizeLabel->setMinimumSize(QSize(100, 40));
        subsetSizeLabel->setMaximumSize(QSize(100, 40));

        horizontalLayout_19->addWidget(subsetSizeLabel);

        subsetSizeText = new QLineEdit(correlationParamsBox);
        subsetSizeText->setObjectName("subsetSizeText");
        subsetSizeText->setEnabled(true);
        sizePolicy3.setHeightForWidth(subsetSizeText->sizePolicy().hasHeightForWidth());
        subsetSizeText->setSizePolicy(sizePolicy3);
        subsetSizeText->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_19->addWidget(subsetSizeText);

        label_5 = new QLabel(correlationParamsBox);
        label_5->setObjectName("label_5");

        horizontalLayout_19->addWidget(label_5);


        verticalLayout_21->addLayout(horizontalLayout_19);

        subsetSizeSlider = new QSlider(correlationParamsBox);
        subsetSizeSlider->setObjectName("subsetSizeSlider");
        subsetSizeSlider->setEnabled(true);
        sizePolicy3.setHeightForWidth(subsetSizeSlider->sizePolicy().hasHeightForWidth());
        subsetSizeSlider->setSizePolicy(sizePolicy3);
        subsetSizeSlider->setMaximumSize(QSize(200, 30));
        subsetSizeSlider->setMinimum(7);
        subsetSizeSlider->setMaximum(201);
        subsetSizeSlider->setSingleStep(2);
        subsetSizeSlider->setPageStep(6);
        subsetSizeSlider->setValue(31);
        subsetSizeSlider->setOrientation(Qt::Horizontal);

        verticalLayout_21->addWidget(subsetSizeSlider);

        verticalSpacer = new QSpacerItem(30, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_21->addItem(verticalSpacer);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName("horizontalLayout_20");
        subsetSpacingLabel = new QLabel(correlationParamsBox);
        subsetSpacingLabel->setObjectName("subsetSpacingLabel");
        sizePolicy3.setHeightForWidth(subsetSpacingLabel->sizePolicy().hasHeightForWidth());
        subsetSpacingLabel->setSizePolicy(sizePolicy3);
        subsetSpacingLabel->setMinimumSize(QSize(100, 40));
        subsetSpacingLabel->setMaximumSize(QSize(100, 40));

        horizontalLayout_20->addWidget(subsetSpacingLabel);

        subsetSpacingText = new QLineEdit(correlationParamsBox);
        subsetSpacingText->setObjectName("subsetSpacingText");
        subsetSpacingText->setEnabled(true);
        sizePolicy3.setHeightForWidth(subsetSpacingText->sizePolicy().hasHeightForWidth());
        subsetSpacingText->setSizePolicy(sizePolicy3);
        subsetSpacingText->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_20->addWidget(subsetSpacingText);

        label_6 = new QLabel(correlationParamsBox);
        label_6->setObjectName("label_6");

        horizontalLayout_20->addWidget(label_6);


        verticalLayout_21->addLayout(horizontalLayout_20);

        subsetSpacingSlider = new QSlider(correlationParamsBox);
        subsetSpacingSlider->setObjectName("subsetSpacingSlider");
        subsetSpacingSlider->setEnabled(true);
        sizePolicy3.setHeightForWidth(subsetSpacingSlider->sizePolicy().hasHeightForWidth());
        subsetSpacingSlider->setSizePolicy(sizePolicy3);
        subsetSpacingSlider->setMaximumSize(QSize(200, 30));
        subsetSpacingSlider->setMinimum(2);
        subsetSpacingSlider->setMaximum(12);
        subsetSpacingSlider->setPageStep(3);
        subsetSpacingSlider->setValue(8);
        subsetSpacingSlider->setOrientation(Qt::Horizontal);

        verticalLayout_21->addWidget(subsetSpacingSlider);


        verticalLayout_22->addLayout(verticalLayout_21);


        verticalLayout_19->addWidget(correlationParamsBox);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        splineLabel = new QLabel(runAnalysis);
        splineLabel->setObjectName("splineLabel");

        horizontalLayout_18->addWidget(splineLabel);

        splineComboBox = new QComboBox(runAnalysis);
        splineComboBox->addItem(QString());
        splineComboBox->addItem(QString());
        splineComboBox->addItem(QString());
        splineComboBox->addItem(QString());
        splineComboBox->setObjectName("splineComboBox");

        horizontalLayout_18->addWidget(splineComboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_2);


        verticalLayout_19->addLayout(horizontalLayout_18);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        researchLabel = new QLabel(runAnalysis);
        researchLabel->setObjectName("researchLabel");

        horizontalLayout_17->addWidget(researchLabel);

        searchRegionSpinBox = new QSpinBox(runAnalysis);
        searchRegionSpinBox->setObjectName("searchRegionSpinBox");
        searchRegionSpinBox->setMinimum(5);
        searchRegionSpinBox->setMaximum(8000);
        searchRegionSpinBox->setSingleStep(10);
        searchRegionSpinBox->setValue(500);

        horizontalLayout_17->addWidget(searchRegionSpinBox);

        label_7 = new QLabel(runAnalysis);
        label_7->setObjectName("label_7");

        horizontalLayout_17->addWidget(label_7);


        verticalLayout_19->addLayout(horizontalLayout_17);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_10 = new QLabel(runAnalysis);
        label_10->setObjectName("label_10");

        horizontalLayout_11->addWidget(label_10);

        corrRejectionLineEdit = new QLineEdit(runAnalysis);
        corrRejectionLineEdit->setObjectName("corrRejectionLineEdit");
        sizePolicy3.setHeightForWidth(corrRejectionLineEdit->sizePolicy().hasHeightForWidth());
        corrRejectionLineEdit->setSizePolicy(sizePolicy3);
        corrRejectionLineEdit->setMinimumSize(QSize(50, 0));
        corrRejectionLineEdit->setMaximumSize(QSize(50, 16777215));
        corrRejectionLineEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(corrRejectionLineEdit);

        label_8 = new QLabel(runAnalysis);
        label_8->setObjectName("label_8");

        horizontalLayout_11->addWidget(label_8);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_6);


        verticalLayout_19->addLayout(horizontalLayout_11);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        analyzeCurrentFrameButton = new QPushButton(runAnalysis);
        analyzeCurrentFrameButton->setObjectName("analyzeCurrentFrameButton");
        sizePolicy3.setHeightForWidth(analyzeCurrentFrameButton->sizePolicy().hasHeightForWidth());
        analyzeCurrentFrameButton->setSizePolicy(sizePolicy3);
        QFont font4;
        font4.setPointSize(8);
        font4.setBold(false);
        analyzeCurrentFrameButton->setFont(font4);
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/resources/1415539747_play_green_controls.png"), QSize(), QIcon::Normal, QIcon::Off);
        analyzeCurrentFrameButton->setIcon(icon23);
        analyzeCurrentFrameButton->setIconSize(QSize(25, 25));

        horizontalLayout_21->addWidget(analyzeCurrentFrameButton);

        analyseAllFramesButton = new QPushButton(runAnalysis);
        analyseAllFramesButton->setObjectName("analyseAllFramesButton");
        sizePolicy3.setHeightForWidth(analyseAllFramesButton->sizePolicy().hasHeightForWidth());
        analyseAllFramesButton->setSizePolicy(sizePolicy3);
        analyseAllFramesButton->setFont(font3);
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/resources/1415539731_play_green.png"), QSize(), QIcon::Normal, QIcon::Off);
        analyseAllFramesButton->setIcon(icon24);
        analyseAllFramesButton->setIconSize(QSize(25, 25));

        horizontalLayout_21->addWidget(analyseAllFramesButton);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_21->addItem(horizontalSpacer_8);


        verticalLayout_19->addLayout(horizontalLayout_21);

        highStrainCheckBox = new QCheckBox(runAnalysis);
        highStrainCheckBox->setObjectName("highStrainCheckBox");
        highStrainCheckBox->setChecked(false);

        verticalLayout_19->addWidget(highStrainCheckBox);

        guiResponsiveCheckBox = new QCheckBox(runAnalysis);
        guiResponsiveCheckBox->setObjectName("guiResponsiveCheckBox");

        verticalLayout_19->addWidget(guiResponsiveCheckBox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_19->addItem(verticalSpacer_2);


        verticalLayout_20->addLayout(verticalLayout_19);

        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/resources/1415619888_processor.png"), QSize(), QIcon::Normal, QIcon::Off);
        modulesToolBox->addItem(runAnalysis, icon25, QString::fromUtf8("Run analysis"));
        resultsDisplay = new QWidget();
        resultsDisplay->setObjectName("resultsDisplay");
        resultsDisplay->setGeometry(QRect(0, 0, 373, 763));
        verticalLayout_8 = new QVBoxLayout(resultsDisplay);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName("verticalLayout_7");
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        dispComboBox = new QComboBox(resultsDisplay);
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->addItem(QString());
        dispComboBox->setObjectName("dispComboBox");
        sizePolicy3.setHeightForWidth(dispComboBox->sizePolicy().hasHeightForWidth());
        dispComboBox->setSizePolicy(sizePolicy3);
        dispComboBox->setMinimumSize(QSize(130, 20));
        dispComboBox->setMaximumSize(QSize(130, 20));
        dispComboBox->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);

        horizontalLayout_7->addWidget(dispComboBox);

        unitsDisplayComboBox = new QComboBox(resultsDisplay);
        unitsDisplayComboBox->addItem(QString());
        unitsDisplayComboBox->addItem(QString());
        unitsDisplayComboBox->addItem(QString());
        unitsDisplayComboBox->addItem(QString());
        unitsDisplayComboBox->addItem(QString());
        unitsDisplayComboBox->addItem(QString());
        unitsDisplayComboBox->setObjectName("unitsDisplayComboBox");
        sizePolicy3.setHeightForWidth(unitsDisplayComboBox->sizePolicy().hasHeightForWidth());
        unitsDisplayComboBox->setSizePolicy(sizePolicy3);

        horizontalLayout_7->addWidget(unitsDisplayComboBox);

        scaleComboBox = new QComboBox(resultsDisplay);
        scaleComboBox->addItem(QString());
        scaleComboBox->addItem(QString());
        scaleComboBox->setObjectName("scaleComboBox");
        sizePolicy3.setHeightForWidth(scaleComboBox->sizePolicy().hasHeightForWidth());
        scaleComboBox->setSizePolicy(sizePolicy3);
        scaleComboBox->setMinimumSize(QSize(100, 20));

        horizontalLayout_7->addWidget(scaleComboBox);


        verticalLayout_7->addLayout(horizontalLayout_7);

        amplifiedMotionBox = new QGroupBox(resultsDisplay);
        amplifiedMotionBox->setObjectName("amplifiedMotionBox");
        sizePolicy7.setHeightForWidth(amplifiedMotionBox->sizePolicy().hasHeightForWidth());
        amplifiedMotionBox->setSizePolicy(sizePolicy7);
        amplifiedMotionBox->setMinimumSize(QSize(0, 100));
        amplifiedMotionBox->setMaximumSize(QSize(16777215, 100));
        amplifiedMotionBox->setSizeIncrement(QSize(0, 200));
        amplifiedMotionBox->setBaseSize(QSize(0, 100));
        verticalLayout_66 = new QVBoxLayout(amplifiedMotionBox);
        verticalLayout_66->setSpacing(6);
        verticalLayout_66->setContentsMargins(11, 11, 11, 11);
        verticalLayout_66->setObjectName("verticalLayout_66");
        verticalLayout_65 = new QVBoxLayout();
        verticalLayout_65->setSpacing(6);
        verticalLayout_65->setObjectName("verticalLayout_65");
        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setSpacing(6);
        horizontalLayout_40->setObjectName("horizontalLayout_40");
        label_9 = new QLabel(amplifiedMotionBox);
        label_9->setObjectName("label_9");

        horizontalLayout_40->addWidget(label_9);

        amplificationSlider = new QSlider(amplifiedMotionBox);
        amplificationSlider->setObjectName("amplificationSlider");
        amplificationSlider->setMinimum(1);
        amplificationSlider->setMaximum(500);
        amplificationSlider->setValue(5);
        amplificationSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_40->addWidget(amplificationSlider);

        amplificationEdit = new QLineEdit(amplifiedMotionBox);
        amplificationEdit->setObjectName("amplificationEdit");
        sizePolicy3.setHeightForWidth(amplificationEdit->sizePolicy().hasHeightForWidth());
        amplificationEdit->setSizePolicy(sizePolicy3);
        amplificationEdit->setMinimumSize(QSize(50, 0));
        amplificationEdit->setMaximumSize(QSize(50, 16777215));
        amplificationEdit->setSizeIncrement(QSize(25, 0));
        amplificationEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_40->addWidget(amplificationEdit);

        ampPercent = new QLabel(amplifiedMotionBox);
        ampPercent->setObjectName("ampPercent");

        horizontalLayout_40->addWidget(ampPercent);


        verticalLayout_65->addLayout(horizontalLayout_40);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(6);
        horizontalLayout_39->setObjectName("horizontalLayout_39");
        label_21 = new QLabel(amplifiedMotionBox);
        label_21->setObjectName("label_21");

        horizontalLayout_39->addWidget(label_21);

        backgroundSlider = new QSlider(amplifiedMotionBox);
        backgroundSlider->setObjectName("backgroundSlider");
        backgroundSlider->setMaximum(100);
        backgroundSlider->setValue(30);
        backgroundSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_39->addWidget(backgroundSlider);

        backgroundEdit = new QLineEdit(amplifiedMotionBox);
        backgroundEdit->setObjectName("backgroundEdit");
        sizePolicy3.setHeightForWidth(backgroundEdit->sizePolicy().hasHeightForWidth());
        backgroundEdit->setSizePolicy(sizePolicy3);
        backgroundEdit->setMinimumSize(QSize(30, 0));
        backgroundEdit->setMaximumSize(QSize(30, 16777215));
        backgroundEdit->setSizeIncrement(QSize(25, 0));
        backgroundEdit->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_39->addWidget(backgroundEdit);

        ampPercent_2 = new QLabel(amplifiedMotionBox);
        ampPercent_2->setObjectName("ampPercent_2");

        horizontalLayout_39->addWidget(ampPercent_2);


        verticalLayout_65->addLayout(horizontalLayout_39);


        verticalLayout_66->addLayout(verticalLayout_65);


        verticalLayout_7->addWidget(amplifiedMotionBox);

        limitGroupBox = new QGroupBox(resultsDisplay);
        limitGroupBox->setObjectName("limitGroupBox");
        sizePolicy7.setHeightForWidth(limitGroupBox->sizePolicy().hasHeightForWidth());
        limitGroupBox->setSizePolicy(sizePolicy7);
        limitGroupBox->setMinimumSize(QSize(0, 200));
        verticalLayout_54 = new QVBoxLayout(limitGroupBox);
        verticalLayout_54->setSpacing(6);
        verticalLayout_54->setContentsMargins(11, 11, 11, 11);
        verticalLayout_54->setObjectName("verticalLayout_54");
        verticalLayout_53 = new QVBoxLayout();
        verticalLayout_53->setSpacing(6);
        verticalLayout_53->setObjectName("verticalLayout_53");
        lowerBoundLabel = new QLabel(limitGroupBox);
        lowerBoundLabel->setObjectName("lowerBoundLabel");
        lowerBoundLabel->setMinimumSize(QSize(0, 15));
        lowerBoundLabel->setMaximumSize(QSize(16777215, 15));
        lowerBoundLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_53->addWidget(lowerBoundLabel);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        groupBox_11 = new QGroupBox(limitGroupBox);
        groupBox_11->setObjectName("groupBox_11");
        groupBox_11->setMinimumSize(QSize(0, 50));
        verticalLayout_11 = new QVBoxLayout(groupBox_11);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName("verticalLayout_11");
        lowerBoundText = new QLineEdit(groupBox_11);
        lowerBoundText->setObjectName("lowerBoundText");
        lowerBoundText->setEnabled(true);
        sizePolicy3.setHeightForWidth(lowerBoundText->sizePolicy().hasHeightForWidth());
        lowerBoundText->setSizePolicy(sizePolicy3);
        lowerBoundText->setMinimumSize(QSize(40, 20));
        lowerBoundText->setMaximumSize(QSize(60, 16777215));

        verticalLayout_11->addWidget(lowerBoundText);


        horizontalLayout_8->addWidget(groupBox_11);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName("verticalLayout_10");
        lowerBoundSlider = new QSlider(limitGroupBox);
        lowerBoundSlider->setObjectName("lowerBoundSlider");
        sizePolicy7.setHeightForWidth(lowerBoundSlider->sizePolicy().hasHeightForWidth());
        lowerBoundSlider->setSizePolicy(sizePolicy7);
        lowerBoundSlider->setMinimumSize(QSize(40, 20));
        lowerBoundSlider->setMaximumSize(QSize(16777215, 20));
        lowerBoundSlider->setMaximum(500);
        lowerBoundSlider->setOrientation(Qt::Horizontal);

        verticalLayout_10->addWidget(lowerBoundSlider);

        upperBoundSlider = new QSlider(limitGroupBox);
        upperBoundSlider->setObjectName("upperBoundSlider");
        QSizePolicy sizePolicy11(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(20);
        sizePolicy11.setHeightForWidth(upperBoundSlider->sizePolicy().hasHeightForWidth());
        upperBoundSlider->setSizePolicy(sizePolicy11);
        upperBoundSlider->setMinimumSize(QSize(40, 20));
        upperBoundSlider->setMaximumSize(QSize(16777215, 20));
        upperBoundSlider->setMaximum(500);
        upperBoundSlider->setValue(500);
        upperBoundSlider->setOrientation(Qt::Horizontal);

        verticalLayout_10->addWidget(upperBoundSlider);


        horizontalLayout_8->addLayout(verticalLayout_10);

        groupBox_12 = new QGroupBox(limitGroupBox);
        groupBox_12->setObjectName("groupBox_12");
        groupBox_12->setMinimumSize(QSize(0, 50));
        verticalLayout_56 = new QVBoxLayout(groupBox_12);
        verticalLayout_56->setSpacing(6);
        verticalLayout_56->setContentsMargins(11, 11, 11, 11);
        verticalLayout_56->setObjectName("verticalLayout_56");
        upperBoundText = new QLineEdit(groupBox_12);
        upperBoundText->setObjectName("upperBoundText");
        upperBoundText->setEnabled(true);
        sizePolicy3.setHeightForWidth(upperBoundText->sizePolicy().hasHeightForWidth());
        upperBoundText->setSizePolicy(sizePolicy3);
        upperBoundText->setMinimumSize(QSize(40, 20));
        upperBoundText->setMaximumSize(QSize(60, 16777215));

        verticalLayout_56->addWidget(upperBoundText);


        horizontalLayout_8->addWidget(groupBox_12);


        verticalLayout_53->addLayout(horizontalLayout_8);

        upperBoundLabel = new QLabel(limitGroupBox);
        upperBoundLabel->setObjectName("upperBoundLabel");
        sizePolicy1.setHeightForWidth(upperBoundLabel->sizePolicy().hasHeightForWidth());
        upperBoundLabel->setSizePolicy(sizePolicy1);
        upperBoundLabel->setMinimumSize(QSize(0, 15));
        upperBoundLabel->setMaximumSize(QSize(16777215, 15));
        upperBoundLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_53->addWidget(upperBoundLabel);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        groupBox_10 = new QGroupBox(limitGroupBox);
        groupBox_10->setObjectName("groupBox_10");
        sizePolicy7.setHeightForWidth(groupBox_10->sizePolicy().hasHeightForWidth());
        groupBox_10->setSizePolicy(sizePolicy7);
        groupBox_10->setMinimumSize(QSize(0, 50));
        groupBox_10->setMaximumSize(QSize(16777215, 50));
        verticalLayout_52 = new QVBoxLayout(groupBox_10);
        verticalLayout_52->setSpacing(6);
        verticalLayout_52->setContentsMargins(11, 11, 11, 11);
        verticalLayout_52->setObjectName("verticalLayout_52");
        colormapSlider = new QSlider(groupBox_10);
        colormapSlider->setObjectName("colormapSlider");
        sizePolicy3.setHeightForWidth(colormapSlider->sizePolicy().hasHeightForWidth());
        colormapSlider->setSizePolicy(sizePolicy3);
        colormapSlider->setMinimumSize(QSize(150, 20));
        colormapSlider->setMaximumSize(QSize(16777215, 20));
        colormapSlider->setMaximum(100);
        colormapSlider->setValue(80);
        colormapSlider->setOrientation(Qt::Horizontal);

        verticalLayout_52->addWidget(colormapSlider);


        horizontalLayout_9->addWidget(groupBox_10);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);


        verticalLayout_53->addLayout(horizontalLayout_9);


        verticalLayout_54->addLayout(verticalLayout_53);


        verticalLayout_7->addWidget(limitGroupBox);

        correlClippingGroupBox = new QGroupBox(resultsDisplay);
        correlClippingGroupBox->setObjectName("correlClippingGroupBox");
        sizePolicy7.setHeightForWidth(correlClippingGroupBox->sizePolicy().hasHeightForWidth());
        correlClippingGroupBox->setSizePolicy(sizePolicy7);
        correlClippingGroupBox->setMinimumSize(QSize(0, 90));
        correlClippingGroupBox->setMaximumSize(QSize(16777215, 90));
        verticalLayout_41 = new QVBoxLayout(correlClippingGroupBox);
        verticalLayout_41->setSpacing(6);
        verticalLayout_41->setContentsMargins(11, 11, 11, 11);
        verticalLayout_41->setObjectName("verticalLayout_41");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        correlClipSlider = new QSlider(correlClippingGroupBox);
        correlClipSlider->setObjectName("correlClipSlider");
        correlClipSlider->setMaximum(500);
        correlClipSlider->setValue(250);
        correlClipSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(correlClipSlider);

        groupBox_9 = new QGroupBox(correlClippingGroupBox);
        groupBox_9->setObjectName("groupBox_9");
        verticalLayout_51 = new QVBoxLayout(groupBox_9);
        verticalLayout_51->setSpacing(6);
        verticalLayout_51->setContentsMargins(11, 11, 11, 11);
        verticalLayout_51->setObjectName("verticalLayout_51");
        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setSpacing(6);
        horizontalLayout_41->setObjectName("horizontalLayout_41");
        clippingValText = new QLineEdit(groupBox_9);
        clippingValText->setObjectName("clippingValText");
        sizePolicy3.setHeightForWidth(clippingValText->sizePolicy().hasHeightForWidth());
        clippingValText->setSizePolicy(sizePolicy3);
        clippingValText->setMinimumSize(QSize(40, 20));
        clippingValText->setMaximumSize(QSize(40, 20));
        clippingValText->setBaseSize(QSize(60, 30));
        clippingValText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_41->addWidget(clippingValText);

        label_11 = new QLabel(groupBox_9);
        label_11->setObjectName("label_11");

        horizontalLayout_41->addWidget(label_11);


        verticalLayout_51->addLayout(horizontalLayout_41);


        horizontalLayout_3->addWidget(groupBox_9);


        verticalLayout_41->addLayout(horizontalLayout_3);


        verticalLayout_7->addWidget(correlClippingGroupBox);

        groupBox_2 = new QGroupBox(resultsDisplay);
        groupBox_2->setObjectName("groupBox_2");
        sizePolicy7.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy7);
        verticalLayout_39 = new QVBoxLayout(groupBox_2);
        verticalLayout_39->setSpacing(6);
        verticalLayout_39->setContentsMargins(11, 11, 11, 11);
        verticalLayout_39->setObjectName("verticalLayout_39");
        verticalLayout_38 = new QVBoxLayout();
        verticalLayout_38->setSpacing(6);
        verticalLayout_38->setObjectName("verticalLayout_38");
        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(6);
        horizontalLayout_32->setObjectName("horizontalLayout_32");
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_35 = new QVBoxLayout(groupBox_3);
        verticalLayout_35->setSpacing(6);
        verticalLayout_35->setContentsMargins(11, 11, 11, 11);
        verticalLayout_35->setObjectName("verticalLayout_35");
        verticalLayout_34 = new QVBoxLayout();
        verticalLayout_34->setSpacing(6);
        verticalLayout_34->setObjectName("verticalLayout_34");
        referenceRadio = new QRadioButton(groupBox_3);
        referenceRadio->setObjectName("referenceRadio");

        verticalLayout_34->addWidget(referenceRadio);

        deformedRadio = new QRadioButton(groupBox_3);
        deformedRadio->setObjectName("deformedRadio");
        deformedRadio->setChecked(true);

        verticalLayout_34->addWidget(deformedRadio);


        verticalLayout_35->addLayout(verticalLayout_34);


        horizontalLayout_32->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName("groupBox_4");
        verticalLayout_37 = new QVBoxLayout(groupBox_4);
        verticalLayout_37->setSpacing(6);
        verticalLayout_37->setContentsMargins(11, 11, 11, 11);
        verticalLayout_37->setObjectName("verticalLayout_37");
        verticalLayout_36 = new QVBoxLayout();
        verticalLayout_36->setSpacing(6);
        verticalLayout_36->setObjectName("verticalLayout_36");
        greenLagrangeRadio = new QRadioButton(groupBox_4);
        greenLagrangeRadio->setObjectName("greenLagrangeRadio");

        verticalLayout_36->addWidget(greenLagrangeRadio);

        greenAlmansiRadio = new QRadioButton(groupBox_4);
        greenAlmansiRadio->setObjectName("greenAlmansiRadio");
        greenAlmansiRadio->setChecked(true);

        verticalLayout_36->addWidget(greenAlmansiRadio);


        verticalLayout_37->addLayout(verticalLayout_36);


        horizontalLayout_32->addWidget(groupBox_4);


        verticalLayout_38->addLayout(horizontalLayout_32);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        showAxesCheckBox = new QCheckBox(groupBox_2);
        showAxesCheckBox->setObjectName("showAxesCheckBox");
        showAxesCheckBox->setChecked(true);

        verticalLayout_3->addWidget(showAxesCheckBox);

        flipXYCheckBox = new QCheckBox(groupBox_2);
        flipXYCheckBox->setObjectName("flipXYCheckBox");

        verticalLayout_3->addWidget(flipXYCheckBox);


        horizontalLayout_6->addLayout(verticalLayout_3);

        cartesianPolarComboBox = new QComboBox(groupBox_2);
        cartesianPolarComboBox->addItem(QString());
        cartesianPolarComboBox->addItem(QString());
        cartesianPolarComboBox->setObjectName("cartesianPolarComboBox");

        horizontalLayout_6->addWidget(cartesianPolarComboBox);


        verticalLayout_38->addLayout(horizontalLayout_6);


        verticalLayout_39->addLayout(verticalLayout_38);


        verticalLayout_7->addWidget(groupBox_2);

        filtersGroupBox = new QGroupBox(resultsDisplay);
        filtersGroupBox->setObjectName("filtersGroupBox");
        sizePolicy7.setHeightForWidth(filtersGroupBox->sizePolicy().hasHeightForWidth());
        filtersGroupBox->setSizePolicy(sizePolicy7);
        verticalLayout_6 = new QVBoxLayout(filtersGroupBox);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName("verticalLayout_6");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName("verticalLayout_4");
        filterLabel = new QLabel(filtersGroupBox);
        filterLabel->setObjectName("filterLabel");

        verticalLayout_4->addWidget(filterLabel);

        filterSlider = new QSlider(filtersGroupBox);
        filterSlider->setObjectName("filterSlider");
        filterSlider->setMinimum(0);
        filterSlider->setMaximum(40);
        filterSlider->setSingleStep(1);
        filterSlider->setPageStep(2);
        filterSlider->setValue(1);
        filterSlider->setSliderPosition(1);
        filterSlider->setTracking(false);
        filterSlider->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(filterSlider);


        horizontalLayout_5->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName("verticalLayout_5");
        gaussianFilterLabel = new QLabel(filtersGroupBox);
        gaussianFilterLabel->setObjectName("gaussianFilterLabel");

        verticalLayout_5->addWidget(gaussianFilterLabel);

        gaussianFilterSlider = new QSlider(filtersGroupBox);
        gaussianFilterSlider->setObjectName("gaussianFilterSlider");
        gaussianFilterSlider->setMinimum(0);
        gaussianFilterSlider->setMaximum(100);
        gaussianFilterSlider->setSingleStep(1);
        gaussianFilterSlider->setPageStep(2);
        gaussianFilterSlider->setValue(1);
        gaussianFilterSlider->setSliderPosition(1);
        gaussianFilterSlider->setTracking(false);
        gaussianFilterSlider->setOrientation(Qt::Horizontal);

        verticalLayout_5->addWidget(gaussianFilterSlider);


        horizontalLayout_5->addLayout(verticalLayout_5);


        verticalLayout_6->addLayout(horizontalLayout_5);


        verticalLayout_7->addWidget(filtersGroupBox);


        verticalLayout_8->addLayout(verticalLayout_7);

        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/resources/1415620325_widescreen_tv.png"), QSize(), QIcon::Normal, QIcon::Off);
        modulesToolBox->addItem(resultsDisplay, icon26, QString::fromUtf8("Format Results"));
        page = new QWidget();
        page->setObjectName("page");
        page->setGeometry(QRect(0, 0, 380, 645));
        verticalLayout_62 = new QVBoxLayout(page);
        verticalLayout_62->setSpacing(6);
        verticalLayout_62->setContentsMargins(11, 11, 11, 11);
        verticalLayout_62->setObjectName("verticalLayout_62");
        verticalLayout_60 = new QVBoxLayout();
        verticalLayout_60->setSpacing(6);
        verticalLayout_60->setObjectName("verticalLayout_60");
        SGGroupBox = new QGroupBox(page);
        SGGroupBox->setObjectName("SGGroupBox");
        verticalLayout_32 = new QVBoxLayout(SGGroupBox);
        verticalLayout_32->setSpacing(6);
        verticalLayout_32->setContentsMargins(11, 11, 11, 11);
        verticalLayout_32->setObjectName("verticalLayout_32");
        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setObjectName("horizontalLayout_36");
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName("verticalLayout_15");
        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setSpacing(6);
        horizontalLayout_34->setObjectName("horizontalLayout_34");
        addStrainGaugeButton = new QPushButton(SGGroupBox);
        addStrainGaugeButton->setObjectName("addStrainGaugeButton");
        addStrainGaugeButton->setEnabled(false);
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/resources/strainGauge.png"), QSize(), QIcon::Normal, QIcon::Off);
        addStrainGaugeButton->setIcon(icon27);
        addStrainGaugeButton->setIconSize(QSize(50, 30));

        horizontalLayout_34->addWidget(addStrainGaugeButton);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_34->addItem(horizontalSpacer_18);


        verticalLayout_15->addLayout(horizontalLayout_34);

        virtualStrainGaugeList = new QListWidget(SGGroupBox);
        virtualStrainGaugeList->setObjectName("virtualStrainGaugeList");
        QSizePolicy sizePolicy12(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(0);
        sizePolicy12.setHeightForWidth(virtualStrainGaugeList->sizePolicy().hasHeightForWidth());
        virtualStrainGaugeList->setSizePolicy(sizePolicy12);
        virtualStrainGaugeList->setMinimumSize(QSize(140, 0));
        virtualStrainGaugeList->setMaximumSize(QSize(140, 16777215));
        virtualStrainGaugeList->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout_15->addWidget(virtualStrainGaugeList);


        horizontalLayout_36->addLayout(verticalLayout_15);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName("verticalLayout_14");
        groupBox_7 = new QGroupBox(SGGroupBox);
        groupBox_7->setObjectName("groupBox_7");
        verticalLayout_48 = new QVBoxLayout(groupBox_7);
        verticalLayout_48->setSpacing(6);
        verticalLayout_48->setContentsMargins(11, 11, 11, 11);
        verticalLayout_48->setObjectName("verticalLayout_48");
        verticalLayout_47 = new QVBoxLayout();
        verticalLayout_47->setSpacing(6);
        verticalLayout_47->setObjectName("verticalLayout_47");
        sgWidthLabel = new QLabel(groupBox_7);
        sgWidthLabel->setObjectName("sgWidthLabel");
        sgWidthLabel->setFrameShape(QFrame::NoFrame);

        verticalLayout_47->addWidget(sgWidthLabel);

        sgOriginLabel = new QLabel(groupBox_7);
        sgOriginLabel->setObjectName("sgOriginLabel");
        sgOriginLabel->setFrameShape(QFrame::NoFrame);

        verticalLayout_47->addWidget(sgOriginLabel);

        sgHeightLabel = new QLabel(groupBox_7);
        sgHeightLabel->setObjectName("sgHeightLabel");

        verticalLayout_47->addWidget(sgHeightLabel);

        sgAngleLabel = new QLabel(groupBox_7);
        sgAngleLabel->setObjectName("sgAngleLabel");

        verticalLayout_47->addWidget(sgAngleLabel);


        verticalLayout_48->addLayout(verticalLayout_47);


        verticalLayout_14->addWidget(groupBox_7);

        groupBox_5 = new QGroupBox(SGGroupBox);
        groupBox_5->setObjectName("groupBox_5");
        verticalLayout_44 = new QVBoxLayout(groupBox_5);
        verticalLayout_44->setSpacing(6);
        verticalLayout_44->setContentsMargins(11, 11, 11, 11);
        verticalLayout_44->setObjectName("verticalLayout_44");
        verticalLayout_43 = new QVBoxLayout();
        verticalLayout_43->setSpacing(6);
        verticalLayout_43->setObjectName("verticalLayout_43");
        e11Label = new QLabel(groupBox_5);
        e11Label->setObjectName("e11Label");

        verticalLayout_43->addWidget(e11Label);

        e22Label = new QLabel(groupBox_5);
        e22Label->setObjectName("e22Label");

        verticalLayout_43->addWidget(e22Label);

        e12Label = new QLabel(groupBox_5);
        e12Label->setObjectName("e12Label");

        verticalLayout_43->addWidget(e12Label);


        verticalLayout_44->addLayout(verticalLayout_43);


        verticalLayout_14->addWidget(groupBox_5);


        horizontalLayout_36->addLayout(verticalLayout_14);


        verticalLayout_32->addLayout(horizontalLayout_36);


        verticalLayout_60->addWidget(SGGroupBox);

        extensometerGroupBox = new QGroupBox(page);
        extensometerGroupBox->setObjectName("extensometerGroupBox");
        verticalLayout_33 = new QVBoxLayout(extensometerGroupBox);
        verticalLayout_33->setSpacing(6);
        verticalLayout_33->setContentsMargins(11, 11, 11, 11);
        verticalLayout_33->setObjectName("verticalLayout_33");
        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setSpacing(6);
        horizontalLayout_37->setObjectName("horizontalLayout_37");
        verticalLayout_23 = new QVBoxLayout();
        verticalLayout_23->setSpacing(6);
        verticalLayout_23->setObjectName("verticalLayout_23");
        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setSpacing(6);
        horizontalLayout_35->setObjectName("horizontalLayout_35");
        addExtensometerButton = new QPushButton(extensometerGroupBox);
        addExtensometerButton->setObjectName("addExtensometerButton");
        addExtensometerButton->setEnabled(false);
        sizePolicy3.setHeightForWidth(addExtensometerButton->sizePolicy().hasHeightForWidth());
        addExtensometerButton->setSizePolicy(sizePolicy3);
        addExtensometerButton->setMinimumSize(QSize(85, 0));
        addExtensometerButton->setMaximumSize(QSize(85, 16777215));
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/resources/extensometer.png"), QSize(), QIcon::Normal, QIcon::Off);
        addExtensometerButton->setIcon(icon28);
        addExtensometerButton->setIconSize(QSize(80, 50));

        horizontalLayout_35->addWidget(addExtensometerButton);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_35->addItem(horizontalSpacer_19);


        verticalLayout_23->addLayout(horizontalLayout_35);

        extensometerList = new QListWidget(extensometerGroupBox);
        extensometerList->setObjectName("extensometerList");
        sizePolicy12.setHeightForWidth(extensometerList->sizePolicy().hasHeightForWidth());
        extensometerList->setSizePolicy(sizePolicy12);
        extensometerList->setMinimumSize(QSize(140, 0));
        extensometerList->setMaximumSize(QSize(140, 16777215));
        extensometerList->setContextMenuPolicy(Qt::CustomContextMenu);

        verticalLayout_23->addWidget(extensometerList);


        horizontalLayout_37->addLayout(verticalLayout_23);

        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setSpacing(6);
        verticalLayout_24->setObjectName("verticalLayout_24");
        groupBox_8 = new QGroupBox(extensometerGroupBox);
        groupBox_8->setObjectName("groupBox_8");
        verticalLayout_50 = new QVBoxLayout(groupBox_8);
        verticalLayout_50->setSpacing(6);
        verticalLayout_50->setContentsMargins(11, 11, 11, 11);
        verticalLayout_50->setObjectName("verticalLayout_50");
        verticalLayout_49 = new QVBoxLayout();
        verticalLayout_49->setSpacing(6);
        verticalLayout_49->setObjectName("verticalLayout_49");
        extPointsLabel = new QLabel(groupBox_8);
        extPointsLabel->setObjectName("extPointsLabel");
        extPointsLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_49->addWidget(extPointsLabel);

        extLengthLabel = new QLabel(groupBox_8);
        extLengthLabel->setObjectName("extLengthLabel");

        verticalLayout_49->addWidget(extLengthLabel);


        verticalLayout_50->addLayout(verticalLayout_49);


        verticalLayout_24->addWidget(groupBox_8);

        groupBox_6 = new QGroupBox(extensometerGroupBox);
        groupBox_6->setObjectName("groupBox_6");
        verticalLayout_46 = new QVBoxLayout(groupBox_6);
        verticalLayout_46->setSpacing(6);
        verticalLayout_46->setContentsMargins(11, 11, 11, 11);
        verticalLayout_46->setObjectName("verticalLayout_46");
        verticalLayout_45 = new QVBoxLayout();
        verticalLayout_45->setSpacing(6);
        verticalLayout_45->setObjectName("verticalLayout_45");
        elongationLabel = new QLabel(groupBox_6);
        elongationLabel->setObjectName("elongationLabel");

        verticalLayout_45->addWidget(elongationLabel);

        elongationXLabel = new QLabel(groupBox_6);
        elongationXLabel->setObjectName("elongationXLabel");

        verticalLayout_45->addWidget(elongationXLabel);

        elongationYLabel = new QLabel(groupBox_6);
        elongationYLabel->setObjectName("elongationYLabel");

        verticalLayout_45->addWidget(elongationYLabel);


        verticalLayout_46->addLayout(verticalLayout_45);


        verticalLayout_24->addWidget(groupBox_6);


        horizontalLayout_37->addLayout(verticalLayout_24);


        verticalLayout_33->addLayout(horizontalLayout_37);


        verticalLayout_60->addWidget(extensometerGroupBox);


        verticalLayout_62->addLayout(verticalLayout_60);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setSpacing(6);
        horizontalLayout_38->setObjectName("horizontalLayout_38");
        horizontalSpacer_22 = new QSpacerItem(50, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_38->addItem(horizontalSpacer_22);

        ppExportButton = new QPushButton(page);
        ppExportButton->setObjectName("ppExportButton");
        sizePolicy3.setHeightForWidth(ppExportButton->sizePolicy().hasHeightForWidth());
        ppExportButton->setSizePolicy(sizePolicy3);
        ppExportButton->setIcon(icon24);
        ppExportButton->setIconSize(QSize(30, 30));

        horizontalLayout_38->addWidget(ppExportButton);


        verticalLayout_62->addLayout(horizontalLayout_38);

        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/resources/1415620049_heart_monitor.png"), QSize(), QIcon::Normal, QIcon::Off);
        modulesToolBox->addItem(page, icon29, QString::fromUtf8("Post-processing tools"));
        exportTools = new QWidget();
        exportTools->setObjectName("exportTools");
        exportTools->setGeometry(QRect(0, 0, 368, 487));
        verticalLayout_27 = new QVBoxLayout(exportTools);
        verticalLayout_27->setSpacing(6);
        verticalLayout_27->setContentsMargins(11, 11, 11, 11);
        verticalLayout_27->setObjectName("verticalLayout_27");
        verticalLayout_25 = new QVBoxLayout();
        verticalLayout_25->setSpacing(6);
        verticalLayout_25->setObjectName("verticalLayout_25");
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName("horizontalLayout_22");
        splitter_2 = new QSplitter(exportTools);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setOrientation(Qt::Vertical);
        xCheck = new QCheckBox(splitter_2);
        xCheck->setObjectName("xCheck");
        splitter_2->addWidget(xCheck);
        yCheck = new QCheckBox(splitter_2);
        yCheck->setObjectName("yCheck");
        splitter_2->addWidget(yCheck);
        rotationCheck = new QCheckBox(splitter_2);
        rotationCheck->setObjectName("rotationCheck");
        splitter_2->addWidget(rotationCheck);
        pStrain1Check = new QCheckBox(splitter_2);
        pStrain1Check->setObjectName("pStrain1Check");
        splitter_2->addWidget(pStrain1Check);
        pStrain2Check = new QCheckBox(splitter_2);
        pStrain2Check->setObjectName("pStrain2Check");
        splitter_2->addWidget(pStrain2Check);
        pDirection1Check = new QCheckBox(splitter_2);
        pDirection1Check->setObjectName("pDirection1Check");
        splitter_2->addWidget(pDirection1Check);
        pDirection2Check = new QCheckBox(splitter_2);
        pDirection2Check->setObjectName("pDirection2Check");
        splitter_2->addWidget(pDirection2Check);
        corrCoefCheck = new QCheckBox(splitter_2);
        corrCoefCheck->setObjectName("corrCoefCheck");
        splitter_2->addWidget(corrCoefCheck);

        horizontalLayout_22->addWidget(splitter_2);

        splitter = new QSplitter(exportTools);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Vertical);
        uCheck = new QCheckBox(splitter);
        uCheck->setObjectName("uCheck");
        splitter->addWidget(uCheck);
        vCheck = new QCheckBox(splitter);
        vCheck->setObjectName("vCheck");
        splitter->addWidget(vCheck);
        exxCheck = new QCheckBox(splitter);
        exxCheck->setObjectName("exxCheck");
        splitter->addWidget(exxCheck);
        eyyCheck = new QCheckBox(splitter);
        eyyCheck->setObjectName("eyyCheck");
        splitter->addWidget(eyyCheck);
        exyCheck = new QCheckBox(splitter);
        exyCheck->setObjectName("exyCheck");
        splitter->addWidget(exyCheck);
        TrescaStrainCheck = new QCheckBox(splitter);
        TrescaStrainCheck->setObjectName("TrescaStrainCheck");
        splitter->addWidget(TrescaStrainCheck);
        vmStrainCheck = new QCheckBox(splitter);
        vmStrainCheck->setObjectName("vmStrainCheck");
        splitter->addWidget(vmStrainCheck);

        horizontalLayout_22->addWidget(splitter);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_13);


        verticalLayout_25->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName("horizontalLayout_23");
        exportTypeComboBox = new QComboBox(exportTools);
        exportTypeComboBox->addItem(QString());
        exportTypeComboBox->addItem(QString());
        exportTypeComboBox->addItem(QString());
        exportTypeComboBox->addItem(QString());
        exportTypeComboBox->addItem(QString());
        exportTypeComboBox->setObjectName("exportTypeComboBox");

        horizontalLayout_23->addWidget(exportTypeComboBox);

        exportCurrentButton = new QPushButton(exportTools);
        exportCurrentButton->setObjectName("exportCurrentButton");
        exportCurrentButton->setIcon(icon23);
        exportCurrentButton->setIconSize(QSize(25, 25));

        horizontalLayout_23->addWidget(exportCurrentButton);


        verticalLayout_25->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName("horizontalLayout_24");
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_12);

        exportAllButton = new QPushButton(exportTools);
        exportAllButton->setObjectName("exportAllButton");
        exportAllButton->setFont(font3);
        exportAllButton->setIcon(icon24);
        exportAllButton->setIconSize(QSize(25, 25));

        horizontalLayout_24->addWidget(exportAllButton);


        verticalLayout_25->addLayout(horizontalLayout_24);

        videoGroupBox = new QGroupBox(exportTools);
        videoGroupBox->setObjectName("videoGroupBox");
        horizontalLayout_28 = new QHBoxLayout(videoGroupBox);
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_28->setObjectName("horizontalLayout_28");
        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName("horizontalLayout_27");
        verticalLayout_26 = new QVBoxLayout();
        verticalLayout_26->setSpacing(6);
        verticalLayout_26->setObjectName("verticalLayout_26");
        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName("horizontalLayout_25");
        frameRateLabel_2 = new QLabel(videoGroupBox);
        frameRateLabel_2->setObjectName("frameRateLabel_2");

        horizontalLayout_25->addWidget(frameRateLabel_2);

        exportFrameRateSpinBox = new QDoubleSpinBox(videoGroupBox);
        exportFrameRateSpinBox->setObjectName("exportFrameRateSpinBox");
        exportFrameRateSpinBox->setDecimals(0);
        exportFrameRateSpinBox->setMinimum(1.000000000000000);
        exportFrameRateSpinBox->setMaximum(60.000000000000000);
        exportFrameRateSpinBox->setValue(5.000000000000000);

        horizontalLayout_25->addWidget(exportFrameRateSpinBox);

        fpsLabel_2 = new QLabel(videoGroupBox);
        fpsLabel_2->setObjectName("fpsLabel_2");

        horizontalLayout_25->addWidget(fpsLabel_2);


        verticalLayout_26->addLayout(horizontalLayout_25);

        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName("horizontalLayout_26");
        videoFormatLabel = new QLabel(videoGroupBox);
        videoFormatLabel->setObjectName("videoFormatLabel");

        horizontalLayout_26->addWidget(videoFormatLabel);

        videoTypeComboBox = new QComboBox(videoGroupBox);
        videoTypeComboBox->addItem(QString());
        videoTypeComboBox->addItem(QString());
        videoTypeComboBox->addItem(QString());
        videoTypeComboBox->setObjectName("videoTypeComboBox");

        horizontalLayout_26->addWidget(videoTypeComboBox);


        verticalLayout_26->addLayout(horizontalLayout_26);


        horizontalLayout_27->addLayout(verticalLayout_26);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_27->addItem(horizontalSpacer_16);

        videoExportButton = new QPushButton(videoGroupBox);
        videoExportButton->setObjectName("videoExportButton");
        sizePolicy3.setHeightForWidth(videoExportButton->sizePolicy().hasHeightForWidth());
        videoExportButton->setSizePolicy(sizePolicy3);
        videoExportButton->setFont(font3);
        QIcon icon30;
        icon30.addFile(QString::fromUtf8(":/resources/1415540011_Movie.png"), QSize(), QIcon::Normal, QIcon::Off);
        videoExportButton->setIcon(icon30);
        videoExportButton->setIconSize(QSize(30, 30));

        horizontalLayout_27->addWidget(videoExportButton);


        horizontalLayout_28->addLayout(horizontalLayout_27);


        verticalLayout_25->addWidget(videoGroupBox);


        verticalLayout_27->addLayout(verticalLayout_25);

        verticalSpacer_4 = new QSpacerItem(20, 152, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_27->addItem(verticalSpacer_4);

        QIcon icon31;
        icon31.addFile(QString::fromUtf8(":/resources/1415620103_upload.png"), QSize(), QIcon::Normal, QIcon::Off);
        modulesToolBox->addItem(exportTools, icon31, QString::fromUtf8("Export tools"));

        horizontalLayout_10->addWidget(modulesToolBox);


        verticalLayout_42->addLayout(horizontalLayout_10);

        OpteCAL->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(OpteCAL);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1232, 32));
        OpteCAL->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OpteCAL);
        mainToolBar->setObjectName("mainToolBar");
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setIconSize(QSize(35, 24));
        OpteCAL->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(OpteCAL);
        statusBar->setObjectName("statusBar");
        OpteCAL->setStatusBar(statusBar);

        mainToolBar->addAction(actionNew_Project);
        mainToolBar->addAction(actionSave_Project);
        mainToolBar->addAction(actionSave_Project_as);
        mainToolBar->addAction(actionLoad_Project);
        mainToolBar->addAction(actionLoad_RAW_files);
        mainToolBar->addAction(actionLoad_experiment_images);

        retranslateUi(OpteCAL);

        loadFilesToolBox->setCurrentIndex(1);
        loadFilesToolBox->layout()->setSpacing(6);
        modulesToolBox->setCurrentIndex(1);
        splineComboBox->setCurrentIndex(1);
        scaleComboBox->setCurrentIndex(0);
        exportTypeComboBox->setCurrentIndex(0);
        videoTypeComboBox->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(OpteCAL);
    } // setupUi

    void retranslateUi(QMainWindow *OpteCAL)
    {
        OpteCAL->setWindowTitle(QCoreApplication::translate("OpteCAL", "OpteCAL", nullptr));
        actionNew_Project->setText(QCoreApplication::translate("OpteCAL", "New Project", nullptr));
#if QT_CONFIG(tooltip)
        actionNew_Project->setToolTip(QCoreApplication::translate("OpteCAL", "New Project (Ctrl+N)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionNew_Project->setShortcut(QCoreApplication::translate("OpteCAL", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLoad_Project->setText(QCoreApplication::translate("OpteCAL", "Open Project", nullptr));
#if QT_CONFIG(tooltip)
        actionLoad_Project->setToolTip(QCoreApplication::translate("OpteCAL", "Open Project (Ctrl+O)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionLoad_Project->setShortcut(QCoreApplication::translate("OpteCAL", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_Project->setText(QCoreApplication::translate("OpteCAL", "Save Project", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_Project->setToolTip(QCoreApplication::translate("OpteCAL", "Save Project (Ctrl+S)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave_Project->setShortcut(QCoreApplication::translate("OpteCAL", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_Project_as->setText(QCoreApplication::translate("OpteCAL", "Save Project as...", nullptr));
#if QT_CONFIG(tooltip)
        actionSave_Project_as->setToolTip(QCoreApplication::translate("OpteCAL", "Save Project as... (Ctrl+Shift+S)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSave_Project_as->setShortcut(QCoreApplication::translate("OpteCAL", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLoad_calibration_images->setText(QCoreApplication::translate("OpteCAL", "Load calibration images", nullptr));
#if QT_CONFIG(shortcut)
        actionLoad_calibration_images->setShortcut(QCoreApplication::translate("OpteCAL", "Ctrl+T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLoad_RAW_files->setText(QCoreApplication::translate("OpteCAL", "Load RAW files", nullptr));
#if QT_CONFIG(shortcut)
        actionLoad_RAW_files->setShortcut(QCoreApplication::translate("OpteCAL", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionLoad_experiment_images->setText(QCoreApplication::translate("OpteCAL", "Load experiment images", nullptr));
#if QT_CONFIG(shortcut)
        actionLoad_experiment_images->setShortcut(QCoreApplication::translate("OpteCAL", "Ctrl+E", nullptr));
#endif // QT_CONFIG(shortcut)
        loadRawImage->setText(QCoreApplication::translate("OpteCAL", "Load RAW files", nullptr));
        labelRaw->setText(QCoreApplication::translate("OpteCAL", "RAW images:", nullptr));
        sortRawFilesComboBox->setItemText(0, QCoreApplication::translate("OpteCAL", "Sort by file name", nullptr));
        sortRawFilesComboBox->setItemText(1, QCoreApplication::translate("OpteCAL", "Sort by date created", nullptr));
        sortRawFilesComboBox->setItemText(2, QCoreApplication::translate("OpteCAL", "Sort by date modified", nullptr));

        loadFilesToolBox->setItemText(loadFilesToolBox->indexOf(rawConverterPage), QCoreApplication::translate("OpteCAL", "Convert Raw images", nullptr));
        loadImageCal->setText(QCoreApplication::translate("OpteCAL", "Load calibration images", nullptr));
        label_2->setText(QCoreApplication::translate("OpteCAL", "Image files:", nullptr));
        sortFilesCalComboBox->setItemText(0, QCoreApplication::translate("OpteCAL", "Sort by file name", nullptr));
        sortFilesCalComboBox->setItemText(1, QCoreApplication::translate("OpteCAL", "Sort by date created", nullptr));
        sortFilesCalComboBox->setItemText(2, QCoreApplication::translate("OpteCAL", "Sort by date modified", nullptr));

        loadFilesToolBox->setItemText(loadFilesToolBox->indexOf(page_5), QCoreApplication::translate("OpteCAL", "Calibration images", nullptr));
        loadImage->setText(QCoreApplication::translate("OpteCAL", "Load experiment images", nullptr));
        label->setText(QCoreApplication::translate("OpteCAL", "Image files:", nullptr));
        sortFilesComboBox->setItemText(0, QCoreApplication::translate("OpteCAL", "Sort by file name", nullptr));
        sortFilesComboBox->setItemText(1, QCoreApplication::translate("OpteCAL", "Sort by date created", nullptr));
        sortFilesComboBox->setItemText(2, QCoreApplication::translate("OpteCAL", "Sort by date modified", nullptr));

        frameRateLabel->setText(QCoreApplication::translate("OpteCAL", "Frame Rate:", nullptr));
        fpsLabel->setText(QCoreApplication::translate("OpteCAL", "fps", nullptr));
        pauseButton->setText(QString());
        playButton->setText(QString());
        loadFilesToolBox->setItemText(loadFilesToolBox->indexOf(page_6), QCoreApplication::translate("OpteCAL", "Experiment images", nullptr));
        currentImgDisplay->setText(QString());
        scaleLabel->setText(QString());
        logoLabel->setText(QString());
        calibrationGroupBox->setTitle(QCoreApplication::translate("OpteCAL", "Distortion correction", nullptr));
        enableCalibrationCheck->setText(QCoreApplication::translate("OpteCAL", "Enable Distortion correction", nullptr));
        groupBox_14->setTitle(QCoreApplication::translate("OpteCAL", "Camera parameters", nullptr));
        label_12->setText(QCoreApplication::translate("OpteCAL", "Camera maker:", nullptr));
        label_13->setText(QCoreApplication::translate("OpteCAL", "Camera model:", nullptr));
        label_17->setText(QCoreApplication::translate("OpteCAL", "Crop factor:", nullptr));
        groupBox_15->setTitle(QCoreApplication::translate("OpteCAL", "Lens parameters", nullptr));
        label_15->setText(QCoreApplication::translate("OpteCAL", "Lens maker:", nullptr));
        label_14->setText(QCoreApplication::translate("OpteCAL", "Lens model:", nullptr));
        label_16->setText(QCoreApplication::translate("OpteCAL", "Focal length:", nullptr));
        label_18->setText(QCoreApplication::translate("OpteCAL", "a:", nullptr));
        label_19->setText(QCoreApplication::translate("OpteCAL", "b:", nullptr));
        label_20->setText(QCoreApplication::translate("OpteCAL", "c:", nullptr));
        rawGroupBox->setTitle(QCoreApplication::translate("OpteCAL", "Raw converter tools", nullptr));
        turnCCWButton->setText(QString());
        turnCWButton->setText(QString());
        convertSelectedButton->setText(QCoreApplication::translate("OpteCAL", "Convert selected files", nullptr));
        convertAllButton->setText(QCoreApplication::translate("OpteCAL", "Convert all files", nullptr));
        groupBox->setTitle(QCoreApplication::translate("OpteCAL", "Camera calibration", nullptr));
        label_4->setText(QCoreApplication::translate("OpteCAL", "Number of chessboard rows:", nullptr));
        label_3->setText(QCoreApplication::translate("OpteCAL", "Number of chessboard columns:", nullptr));
        findCornersButton->setText(QCoreApplication::translate("OpteCAL", "Find checkerboard", nullptr));
        calibratePushButton->setText(QCoreApplication::translate("OpteCAL", "Calibrate", nullptr));
        modulesToolBox->setItemText(modulesToolBox->indexOf(calibration), QCoreApplication::translate("OpteCAL", "Calibrate", nullptr));
        roiGroupBox->setTitle(QCoreApplication::translate("OpteCAL", "Region of Interest drawing tools", nullptr));
        plusPolyButton->setText(QString());
        minusPolyButton->setText(QString());
        plusCircleButton->setText(QString());
        minusCircleButton->setText(QString());
        lengthCalibrateGroupBox->setTitle(QCoreApplication::translate("OpteCAL", "Scale definition", nullptr));
        pixelLineEdit->setText(QCoreApplication::translate("OpteCAL", "1", nullptr));
        pixelsLabel->setText(QCoreApplication::translate("OpteCAL", "pixels", nullptr));
        equalLabel->setText(QCoreApplication::translate("OpteCAL", "=", nullptr));
        unitLineEdit->setText(QCoreApplication::translate("OpteCAL", "1", nullptr));
        unitComboBox->setItemText(0, QCoreApplication::translate("OpteCAL", "mm", nullptr));
        unitComboBox->setItemText(1, QCoreApplication::translate("OpteCAL", "cm", nullptr));
        unitComboBox->setItemText(2, QCoreApplication::translate("OpteCAL", "m", nullptr));
        unitComboBox->setItemText(3, QCoreApplication::translate("OpteCAL", "inches", nullptr));
        unitComboBox->setItemText(4, QCoreApplication::translate("OpteCAL", "feet", nullptr));

        applyScaleButton->setText(QCoreApplication::translate("OpteCAL", "Apply", nullptr));
        measureButton->setText(QCoreApplication::translate("OpteCAL", "measure...", nullptr));
        pixelEURatioLabel->setText(QCoreApplication::translate("OpteCAL", "pixel/mm ratio = Undefined", nullptr));
        modulesToolBox->setItemText(modulesToolBox->indexOf(drawRoi), QCoreApplication::translate("OpteCAL", "Set up project properties", nullptr));
        setSeedButton->setText(QCoreApplication::translate("OpteCAL", "Add seed", nullptr));
        correlationParamsBox->setTitle(QCoreApplication::translate("OpteCAL", "Subset parameters:", nullptr));
        subsetSizeLabel->setText(QCoreApplication::translate("OpteCAL", "Subset Size:", nullptr));
        subsetSizeText->setText(QCoreApplication::translate("OpteCAL", "45", nullptr));
        label_5->setText(QCoreApplication::translate("OpteCAL", "pixels", nullptr));
        subsetSpacingLabel->setText(QCoreApplication::translate("OpteCAL", "Subset Spacing:", nullptr));
        subsetSpacingText->setText(QCoreApplication::translate("OpteCAL", "13", nullptr));
        label_6->setText(QCoreApplication::translate("OpteCAL", "pixels", nullptr));
        splineLabel->setText(QCoreApplication::translate("OpteCAL", "Spline interpolation:", nullptr));
        splineComboBox->setItemText(0, QCoreApplication::translate("OpteCAL", "3rd order", nullptr));
        splineComboBox->setItemText(1, QCoreApplication::translate("OpteCAL", "5th order (default)", nullptr));
        splineComboBox->setItemText(2, QCoreApplication::translate("OpteCAL", "7th order", nullptr));
        splineComboBox->setItemText(3, QCoreApplication::translate("OpteCAL", "9th order", nullptr));

        researchLabel->setText(QCoreApplication::translate("OpteCAL", "Search region of the seed: ", nullptr));
        label_7->setText(QCoreApplication::translate("OpteCAL", "pixels", nullptr));
        label_10->setText(QCoreApplication::translate("OpteCAL", "Correlation coef. rejection:", nullptr));
        corrRejectionLineEdit->setText(QCoreApplication::translate("OpteCAL", "10", nullptr));
        label_8->setText(QCoreApplication::translate("OpteCAL", "% subset match", nullptr));
        analyzeCurrentFrameButton->setText(QCoreApplication::translate("OpteCAL", "Analyze selected images", nullptr));
        analyseAllFramesButton->setText(QCoreApplication::translate("OpteCAL", "Analyze all images", nullptr));
        highStrainCheckBox->setText(QCoreApplication::translate("OpteCAL", "Perform high-strain analysis (updated reference image)", nullptr));
        guiResponsiveCheckBox->setText(QCoreApplication::translate("OpteCAL", "Use all CPU resources (Computer may not be responsive)", nullptr));
        modulesToolBox->setItemText(modulesToolBox->indexOf(runAnalysis), QCoreApplication::translate("OpteCAL", "Run analysis", nullptr));
        dispComboBox->setItemText(0, QCoreApplication::translate("OpteCAL", "U", nullptr));
        dispComboBox->setItemText(1, QCoreApplication::translate("OpteCAL", "V", nullptr));
        dispComboBox->setItemText(2, QCoreApplication::translate("OpteCAL", "Rotation", nullptr));
        dispComboBox->setItemText(3, QCoreApplication::translate("OpteCAL", "Exx", nullptr));
        dispComboBox->setItemText(4, QCoreApplication::translate("OpteCAL", "Eyy", nullptr));
        dispComboBox->setItemText(5, QCoreApplication::translate("OpteCAL", "Exy", nullptr));
        dispComboBox->setItemText(6, QCoreApplication::translate("OpteCAL", "Principal Strain 1", nullptr));
        dispComboBox->setItemText(7, QCoreApplication::translate("OpteCAL", "Principal Strain 2", nullptr));
        dispComboBox->setItemText(8, QCoreApplication::translate("OpteCAL", "Principal Dir. 1", nullptr));
        dispComboBox->setItemText(9, QCoreApplication::translate("OpteCAL", "Principal Dir. 2", nullptr));
        dispComboBox->setItemText(10, QCoreApplication::translate("OpteCAL", "Von-Mises Strain", nullptr));
        dispComboBox->setItemText(11, QCoreApplication::translate("OpteCAL", "Tresca Strain", nullptr));
        dispComboBox->setItemText(12, QCoreApplication::translate("OpteCAL", "Cor. coeff.", nullptr));
        dispComboBox->setItemText(13, QCoreApplication::translate("OpteCAL", "X", nullptr));
        dispComboBox->setItemText(14, QCoreApplication::translate("OpteCAL", "Y", nullptr));

        unitsDisplayComboBox->setItemText(0, QCoreApplication::translate("OpteCAL", "pixels", nullptr));
        unitsDisplayComboBox->setItemText(1, QCoreApplication::translate("OpteCAL", "mm", nullptr));
        unitsDisplayComboBox->setItemText(2, QCoreApplication::translate("OpteCAL", "cm", nullptr));
        unitsDisplayComboBox->setItemText(3, QCoreApplication::translate("OpteCAL", "m", nullptr));
        unitsDisplayComboBox->setItemText(4, QCoreApplication::translate("OpteCAL", "inches", nullptr));
        unitsDisplayComboBox->setItemText(5, QCoreApplication::translate("OpteCAL", "feet", nullptr));

        scaleComboBox->setItemText(0, QCoreApplication::translate("OpteCAL", "Manual scale", nullptr));
        scaleComboBox->setItemText(1, QCoreApplication::translate("OpteCAL", "Auto scale", nullptr));

        amplifiedMotionBox->setTitle(QCoreApplication::translate("OpteCAL", "Amplified motion", nullptr));
        label_9->setText(QCoreApplication::translate("OpteCAL", "Amplification:", nullptr));
        amplificationEdit->setText(QCoreApplication::translate("OpteCAL", "5", nullptr));
        ampPercent->setText(QCoreApplication::translate("OpteCAL", "x", nullptr));
        label_21->setText(QCoreApplication::translate("OpteCAL", "Background:", nullptr));
        backgroundEdit->setText(QCoreApplication::translate("OpteCAL", "30", nullptr));
        ampPercent_2->setText(QCoreApplication::translate("OpteCAL", "%", nullptr));
        limitGroupBox->setTitle(QCoreApplication::translate("OpteCAL", "Colormap", nullptr));
        lowerBoundLabel->setText(QCoreApplication::translate("OpteCAL", "Lower bound slider", nullptr));
        groupBox_11->setTitle(QCoreApplication::translate("OpteCAL", "Slider min", nullptr));
        lowerBoundText->setText(QCoreApplication::translate("OpteCAL", "0", nullptr));
        groupBox_12->setTitle(QCoreApplication::translate("OpteCAL", "Slider max", nullptr));
        upperBoundText->setText(QCoreApplication::translate("OpteCAL", "1", nullptr));
        upperBoundLabel->setText(QCoreApplication::translate("OpteCAL", "Upper bound slider", nullptr));
        groupBox_10->setTitle(QCoreApplication::translate("OpteCAL", "Transparency", nullptr));
        correlClippingGroupBox->setTitle(QCoreApplication::translate("OpteCAL", "Correlation coefficient clipping:", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("OpteCAL", "Slider bound", nullptr));
        clippingValText->setText(QCoreApplication::translate("OpteCAL", "10", nullptr));
        label_11->setText(QCoreApplication::translate("OpteCAL", "% match", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("OpteCAL", "Coordinate system", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("OpteCAL", "Configuration", nullptr));
        referenceRadio->setText(QCoreApplication::translate("OpteCAL", "Reference", nullptr));
        deformedRadio->setText(QCoreApplication::translate("OpteCAL", "Deformed", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("OpteCAL", "Strain definition", nullptr));
        greenLagrangeRadio->setText(QCoreApplication::translate("OpteCAL", "Material (Green-Lagrange)", nullptr));
        greenAlmansiRadio->setText(QCoreApplication::translate("OpteCAL", "Spatial (Green-Almansi)", nullptr));
        showAxesCheckBox->setText(QCoreApplication::translate("OpteCAL", "Show Axes", nullptr));
        flipXYCheckBox->setText(QCoreApplication::translate("OpteCAL", "Flip X and Y", nullptr));
        cartesianPolarComboBox->setItemText(0, QCoreApplication::translate("OpteCAL", "Cartesian coordinates", nullptr));
        cartesianPolarComboBox->setItemText(1, QCoreApplication::translate("OpteCAL", "Polar coordinates", nullptr));

        filtersGroupBox->setTitle(QCoreApplication::translate("OpteCAL", "Filters", nullptr));
        filterLabel->setText(QCoreApplication::translate("OpteCAL", "Median filter:", nullptr));
        gaussianFilterLabel->setText(QCoreApplication::translate("OpteCAL", "Gaussian filter:", nullptr));
        modulesToolBox->setItemText(modulesToolBox->indexOf(resultsDisplay), QCoreApplication::translate("OpteCAL", "Format Results", nullptr));
        SGGroupBox->setTitle(QCoreApplication::translate("OpteCAL", "Virtual strain gauge", nullptr));
        addStrainGaugeButton->setText(QString());
        groupBox_7->setTitle(QCoreApplication::translate("OpteCAL", "Strain gauge parameters:", nullptr));
        sgWidthLabel->setText(QCoreApplication::translate("OpteCAL", "Width: NaN", nullptr));
        sgOriginLabel->setText(QCoreApplication::translate("OpteCAL", "Origin: (NaN,NaN)", nullptr));
        sgHeightLabel->setText(QCoreApplication::translate("OpteCAL", "Height: NaN", nullptr));
        sgAngleLabel->setText(QCoreApplication::translate("OpteCAL", "Angle: NaN", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("OpteCAL", "Strain:", nullptr));
        e11Label->setText(QCoreApplication::translate("OpteCAL", "E11 = NaN", nullptr));
        e22Label->setText(QCoreApplication::translate("OpteCAL", "E22 = NaN", nullptr));
        e12Label->setText(QCoreApplication::translate("OpteCAL", "E12 = NaN", nullptr));
        extensometerGroupBox->setTitle(QCoreApplication::translate("OpteCAL", "Virtual extensometer", nullptr));
        addExtensometerButton->setText(QString());
        groupBox_8->setTitle(QCoreApplication::translate("OpteCAL", "Extensometer parameters:", nullptr));
        extPointsLabel->setText(QCoreApplication::translate("OpteCAL", "Anchor points: (NaN,NaN)\n"
"(NaN,NaN)", nullptr));
        extLengthLabel->setText(QCoreApplication::translate("OpteCAL", "Length: NaN", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("OpteCAL", "Elongation:", nullptr));
        elongationLabel->setText(QCoreApplication::translate("OpteCAL", "Elongation = NaN", nullptr));
        elongationXLabel->setText(QCoreApplication::translate("OpteCAL", "x-Projection = NaN", nullptr));
        elongationYLabel->setText(QCoreApplication::translate("OpteCAL", "y-Projection = NaN", nullptr));
        ppExportButton->setText(QCoreApplication::translate("OpteCAL", "Create data table", nullptr));
        modulesToolBox->setItemText(modulesToolBox->indexOf(page), QCoreApplication::translate("OpteCAL", "Post-processing tools", nullptr));
        xCheck->setText(QCoreApplication::translate("OpteCAL", "X", nullptr));
        yCheck->setText(QCoreApplication::translate("OpteCAL", "Y", nullptr));
        rotationCheck->setText(QCoreApplication::translate("OpteCAL", "Rotation", nullptr));
        pStrain1Check->setText(QCoreApplication::translate("OpteCAL", "Principal strain 1", nullptr));
        pStrain2Check->setText(QCoreApplication::translate("OpteCAL", "Principal strain 2", nullptr));
        pDirection1Check->setText(QCoreApplication::translate("OpteCAL", "Principal direction 1", nullptr));
        pDirection2Check->setText(QCoreApplication::translate("OpteCAL", "Principal direction 2", nullptr));
        corrCoefCheck->setText(QCoreApplication::translate("OpteCAL", "Correlation coefficient", nullptr));
        uCheck->setText(QCoreApplication::translate("OpteCAL", "U", nullptr));
        vCheck->setText(QCoreApplication::translate("OpteCAL", "V", nullptr));
        exxCheck->setText(QCoreApplication::translate("OpteCAL", "Exx", nullptr));
        eyyCheck->setText(QCoreApplication::translate("OpteCAL", "Eyy", nullptr));
        exyCheck->setText(QCoreApplication::translate("OpteCAL", "Exy", nullptr));
        TrescaStrainCheck->setText(QCoreApplication::translate("OpteCAL", "Tresca Strain", nullptr));
        vmStrainCheck->setText(QCoreApplication::translate("OpteCAL", "Von-Mises Strain", nullptr));
        exportTypeComboBox->setItemText(0, QCoreApplication::translate("OpteCAL", "JPEG", nullptr));
        exportTypeComboBox->setItemText(1, QCoreApplication::translate("OpteCAL", "TIFF (LZW compression)", nullptr));
        exportTypeComboBox->setItemText(2, QCoreApplication::translate("OpteCAL", "BMP (uncompressed)", nullptr));
        exportTypeComboBox->setItemText(3, QCoreApplication::translate("OpteCAL", "CSV file", nullptr));
        exportTypeComboBox->setItemText(4, QCoreApplication::translate("OpteCAL", "Matlab file (.mat)", nullptr));

        exportCurrentButton->setText(QCoreApplication::translate("OpteCAL", "Export selected frames", nullptr));
        exportAllButton->setText(QCoreApplication::translate("OpteCAL", "Export all frames", nullptr));
        videoGroupBox->setTitle(QCoreApplication::translate("OpteCAL", "Video export parameters", nullptr));
        frameRateLabel_2->setText(QCoreApplication::translate("OpteCAL", "Frame Rate:", nullptr));
        fpsLabel_2->setText(QCoreApplication::translate("OpteCAL", "fps", nullptr));
        videoFormatLabel->setText(QCoreApplication::translate("OpteCAL", "Quality", nullptr));
        videoTypeComboBox->setItemText(0, QCoreApplication::translate("OpteCAL", "SD", nullptr));
        videoTypeComboBox->setItemText(1, QCoreApplication::translate("OpteCAL", "HD", nullptr));
        videoTypeComboBox->setItemText(2, QCoreApplication::translate("OpteCAL", "Ultra HD", nullptr));

        videoExportButton->setText(QCoreApplication::translate("OpteCAL", "Export video", nullptr));
        modulesToolBox->setItemText(modulesToolBox->indexOf(exportTools), QCoreApplication::translate("OpteCAL", "Export tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OpteCAL: public Ui_OpteCAL {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTECAL_H
