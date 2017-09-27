#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <vector>
#include "mydatastore.h"
#include <QWidget>
#include <QComboBox>
#include <QListWidget>
#include <QLineEdit>
#include <msort.h>
#include <QCoreApplication>
#include <fstream>
#include <QTextEdit>
#include <string>

class MainWindow : public QWidget {
	Q_OBJECT

	public:
		MainWindow(MyDataStore* ds);
		~MainWindow();
		void insertUsers();


	private slots:
		void andButtonClicked();
		void orButtonClicked();		
		void addToCart();
		void showPopup();
		void close();
		void buyCart();
		void removeItemFromCart();
		void displayReviews();
		void closeReviewLayout();
		void exit();
		void saveToDatabase();
		void addReview();
		void populateReviews();
		void closeAddWindow();

	private:
		MyDataStore* mds;

		QHBoxLayout* overallLayout;
		//left
		QVBoxLayout* leftCol;
		QLabel* selectUserLabel;
		QComboBox* selectUser;
		//mid
		QVBoxLayout* midCol;

		QLabel* searchLabel;
		QLabel* radioLabel;

		QHBoxLayout* searchInterface;
		QLineEdit* searchBox;
		QPushButton* andButton;
		QPushButton* orButton;

		QHBoxLayout* resultInterface;
		QListWidget* searchResults;
		QComboBox* selectSort;

		QHBoxLayout* reviewInterface;

		//right
		QVBoxLayout* rightCol;
		QPushButton* addCart;
		QPushButton* viewCart;
		QPushButton* viewReviews;
		QPushButton* addReviewButton;

		QHBoxLayout* saveFile;
		QLineEdit* filename;
		QPushButton* save;

		QPushButton* quit;

		//popUp
		QWidget* popUpWindow;
		QHBoxLayout* popUpOverall;
		QVBoxLayout* oneCol;

		//view cart
		QListWidget* cartResults;


		//buttons
		QHBoxLayout* buttonLayout;
		QPushButton* buyButton;
		QPushButton* removeButton;
		QPushButton* closeButton;

		//display reviews
		QWidget* reviewWindow;
		QHBoxLayout* reviewOverall;		
		QVBoxLayout* reviewCol;
		QListWidget* reviewResults;
		QPushButton* reviewCloseButton;

		//addReview
		QWidget* addReviewWindow;
		QHBoxLayout* addReviewOverall;
		QVBoxLayout* addReviewCol;

		QLabel* reviewRatingLabel;
		QComboBox* reviewRating;
	    
	    QLabel* dateLabel;
	    QHBoxLayout* dateLayout;
		QComboBox* day;
		QComboBox* month;
		QComboBox* year;

		QLabel* enterReview;
	    QTextEdit* reviewText;

	    QHBoxLayout* addReviewButtonLayout;
    	QPushButton* finishedReview;
    	QPushButton* closeAddReview;


		std::vector<Product*> hits;

};

#endif