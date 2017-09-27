#include "main_window.h"
#include <sstream>

using namespace std;

MainWindow::MainWindow(MyDataStore* ds): mds(ds)
{
	setWindowTitle("Amazon");

	//delegate columns
	overallLayout =  new QHBoxLayout();

	leftCol = new QVBoxLayout();
	midCol = new QVBoxLayout();
	rightCol = new QVBoxLayout();

	overallLayout->addLayout(leftCol);
	overallLayout->addLayout(midCol);
	overallLayout->addLayout(rightCol);

	//left col set up
	selectUserLabel = new QLabel("Select User");
	selectUser = new QComboBox(); //need to add users

	vector<User*> tempUsers = mds->getUsers();

	for (unsigned int i=0; i < tempUsers.size(); i++)
	{		
		selectUser->addItem(QString::fromStdString(tempUsers[i]->getName()));
	}

	leftCol->addWidget(selectUserLabel);
	leftCol->addWidget(selectUser);

	//mid col setup
	searchLabel = new QLabel("Enter Search Term");
	radioLabel = new QLabel("Choose which search type");

	searchBox = new QLineEdit();

	andButton = new QPushButton("AND");
	orButton = new QPushButton("OR");

	connect(andButton, SIGNAL(clicked()), this, SLOT(andButtonClicked()));
	connect(orButton, SIGNAL(clicked()), this, SLOT(orButtonClicked()));

	resultInterface = new QHBoxLayout();
	searchResults = new QListWidget();
	selectSort = new QComboBox(); //add options

	selectSort->addItem(QString::fromStdString("Alphabetical"));
	selectSort->addItem(QString::fromStdString("Avg Rating"));



	resultInterface->addWidget(searchResults);
	resultInterface->addWidget(selectSort);


	midCol->addWidget(searchLabel);
	midCol->addWidget(searchBox);
	midCol->addWidget(radioLabel);
	midCol->addWidget(andButton);
	midCol->addWidget(orButton);

	midCol->addLayout(resultInterface);


	//right col setup
	addCart = new QPushButton("Add to Cart");
	viewCart = new QPushButton("View Cart");
	viewReviews = new QPushButton("View Product Reviews");
	quit = new QPushButton("Exit");
	save = new QPushButton("Save File");
	addReviewButton = new QPushButton("Add Review");

	saveFile = new QHBoxLayout();
	filename = new QLineEdit();

	saveFile->addWidget(filename);
	saveFile->addWidget(save);

	rightCol->addWidget(addCart);
	rightCol->addWidget(viewCart);
	rightCol->addWidget(viewReviews);
	rightCol->addLayout(saveFile);
	rightCol->addWidget(addReviewButton);
	rightCol->addWidget(quit);

	connect(addCart, SIGNAL(clicked()), this, SLOT(addToCart()));
	connect(quit, SIGNAL(clicked()), this, SLOT(exit()));
	//save to database
	connect(save, SIGNAL(clicked()), this, SLOT(saveToDatabase()));


	//popup
	popUpWindow = new QWidget();
	popUpOverall = new QHBoxLayout();	

	popUpWindow->setLayout(popUpOverall);

	oneCol = new QVBoxLayout();

	//view cart
	cartResults = new QListWidget();

	//buttons
	buttonLayout = new QHBoxLayout();
	buyButton = new QPushButton("Buy Cart");
	removeButton = new QPushButton("Remove From Cart");
	closeButton = new QPushButton("Cancel");

	
	popUpOverall->addLayout(oneCol);
	oneCol->addWidget(cartResults);
	oneCol->addLayout(buttonLayout);
	buttonLayout->addWidget(buyButton);
	buttonLayout->addWidget(removeButton);
	buttonLayout->addWidget(closeButton);
	connect(viewCart, SIGNAL(clicked()), this, SLOT(showPopup()));
	//close button
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

	//buyCart
	connect(buyButton, SIGNAL(clicked()), this, SLOT(buyCart()));

	//remove item from cart
	connect(removeButton, SIGNAL(clicked()), this, SLOT(removeItemFromCart()));

	//display reviews widget
	reviewWindow = new QWidget();
	reviewOverall = new QHBoxLayout();
	reviewCol = new QVBoxLayout();
	reviewResults = new QListWidget();
	//buttons
	reviewCloseButton = new QPushButton("Cancel");
	reviewWindow->setLayout(reviewOverall);
	reviewOverall->addLayout(reviewCol);
	reviewCol->addWidget(reviewResults);
	reviewCol->addWidget(reviewCloseButton);

	connect(viewReviews, SIGNAL(clicked()), this, SLOT(displayReviews()));

	//close review window
	connect(reviewCloseButton, SIGNAL(clicked()), this, SLOT(closeReviewLayout()));


	//review window
	addReviewWindow = new QWidget();
	addReviewOverall = new QHBoxLayout();
	addReviewCol = new QVBoxLayout();

	addReviewOverall->addLayout(addReviewCol);

	reviewRatingLabel = new QLabel("Rating:");
	reviewRating = new QComboBox();

	addReviewCol->addWidget(reviewRatingLabel);
	addReviewCol->addWidget(reviewRating);
    
    dateLabel = new QLabel("Enter Date:");
    dateLayout = new QHBoxLayout();
	day = new QComboBox();
	month = new QComboBox();
	year = new QComboBox();

	dateLayout->addWidget(dateLabel);
	dateLayout->addWidget(day);
	dateLayout->addWidget(month);
	dateLayout->addWidget(year);
	//add
	addReviewCol->addLayout(dateLayout);

	enterReview = new QLabel("Enter Review:");
    reviewText = new QTextEdit();

    addReviewCol->addWidget(enterReview);
    addReviewCol->addWidget(reviewText);

    QHBoxLayout* addReviewButtonLayout = new QHBoxLayout();
    QPushButton* finishedReview = new QPushButton("Add");
    QPushButton* closeAddReview = new QPushButton("Close");

    addReviewButtonLayout->addWidget(finishedReview);
    addReviewButtonLayout->addWidget(closeAddReview);

    addReviewCol->addLayout(addReviewButtonLayout);

    addReviewWindow->setLayout(addReviewOverall);



    //add review connect
    connect(addReviewButton, SIGNAL(clicked()), this, SLOT(addReview()));
    connect(closeAddReview, SIGNAL(clicked()), this, SLOT(closeAddWindow()));
    connect(finishedReview, SIGNAL(clicked()), this, SLOT(populateReviews()));


	setLayout(overallLayout);
}
MainWindow::~MainWindow()
{

}

void MainWindow::andButtonClicked()
{
	searchResults->clear();
	std::string searchTerms = searchBox->text().toStdString();
	stringstream ss(searchTerms);

	string temp;
	vector<std::string> terms;
	while (ss >> temp)
	{
		terms.push_back(temp);
	}


	hits = mds->search(terms,0);
	string sortType = selectSort->currentText().toStdString();

	if (sortType == "Alphabetical")
	{
		ProductName a;
		merge_sort(hits, a);
	}
	if (sortType == "Ratings")
	{
		Ratings r;
		merge_sort(hits,r);
	}

	for (unsigned int i=0; i < hits.size(); i++)
	{
		string temp = hits[i]->displayString();
		QString qstr = QString::fromStdString(temp);
		searchResults->addItem(qstr);		
	}


}

void MainWindow::orButtonClicked()
{
	searchResults->clear();
	std::string searchTerms = searchBox->text().toStdString();
	stringstream ss(searchTerms);

	string temp;
	vector<std::string> terms;
	while (ss >> temp)
	{
		terms.push_back(temp);
	}

	hits = mds->search(terms,1);
	string sortType = selectSort->currentText().toStdString();

	if (sortType == "Alphabetical")
	{
		ProductName a;
		merge_sort(hits, a);
	}
	if (sortType == "Ratings")
	{
		Ratings r;
		merge_sort(hits,r);
	}

	for (unsigned int i=0; i < hits.size(); i++)
	{
		string temp = hits[i]->displayString();
		QString qstr = QString::fromStdString(temp);
		searchResults->addItem(qstr);
	}



}
void MainWindow::addToCart()
{
	//get highlighted user
	string currUser = selectUser->currentText().toStdString();
	//get the product selected
	int currIndex = searchResults->currentRow();
	mds->addToCart(currUser, hits, currIndex );

}

void MainWindow::showPopup()
{
	cartResults->clear();
	//populate the cart Results
	string currUser = selectUser->currentText().toStdString();
	User* temp = mds->getUserFromName(currUser);
	queue<Product*> cart = mds->getUserCart(temp);

	unsigned int size = cart.size();
	for (unsigned int i=0; i < size; i++)
    {
        Product* p = cart.front();
        QString qstr = QString::fromStdString(p->displayString());
		cartResults->addItem(qstr);  
        cart.pop();
        cart.push(p);
    }


	popUpWindow->show();
}
void MainWindow::close()
{
	popUpWindow->close();
}
void MainWindow::buyCart()
{
	string currUser = selectUser->currentText().toStdString();
	mds->buyCart(currUser);
	showPopup();
}
void MainWindow::removeItemFromCart()
{
	unsigned int currIndex = cartResults->currentRow();
	string currUser = selectUser->currentText().toStdString();

	mds->removeFromCart(currUser, currIndex);

    showPopup();

}
void MainWindow::displayReviews()
{
	reviewResults->clear();
	int currIndex = searchResults->currentRow();

	if (currIndex < 0) return;

	vector<Review*> reviews = mds->getReviews();

	Product* p = hits[currIndex];
	string productName = p->getName();

	vector<Review*> associatedWithProduct;

	for (unsigned int i=0; i < reviews.size(); i++)
	{
		if (productName == reviews[i]->prodName)
		{
			associatedWithProduct.push_back(reviews[i]);
			
		}
	}
	ReviewDate r;
	merge_sort(associatedWithProduct,r);

	for (unsigned int i=0; i < associatedWithProduct.size(); i++)
	{
		stringstream ss;
		ss << associatedWithProduct[i]->prodName << endl;
		ss << associatedWithProduct[i]->rating << " " << associatedWithProduct[i]->username << " ";
		ss << associatedWithProduct[i]->date <<" "<<associatedWithProduct[i]->reviewText;
		ss << endl;
		string temp = ss.str();
		QString qstr = QString::fromStdString(temp);
		reviewResults->addItem(qstr);		
	}
	

	reviewWindow->show();
}
void MainWindow::closeReviewLayout()
{
	reviewWindow->close();
}

void MainWindow::exit()
{
	QCoreApplication::instance()->exit();
}
void MainWindow::saveToDatabase()
{
	string fileName = filename->text().toStdString();
	if (fileName == "")
	{
		return;
	}	
    ofstream ofile(fileName.c_str());
    mds->dump(ofile);
    ofile.close();
}
void MainWindow::addReview()
{
	int currIndex = searchResults->currentRow();
	if (currIndex < 0)
		return;

	//reviewRating->addItem(QString::fromStdString(i);
	for (int i=1; i <= 5; i++)
	{
		stringstream ss;
		ss << i;
		string x = ss.str();
		reviewRating->addItem(QString::fromStdString(x));
	}

	for (int i = 1970; i <= 2017; i++)
	{
		stringstream ss;
		ss << i;
		string x = ss.str();
		year->addItem(QString::fromStdString(x));
	}

	for (int i = 1; i <= 12; i++)
	{
		stringstream ss;
		if (i < 10)
			ss << "0";
		ss << i;
		string x = ss.str();
		month->addItem(QString::fromStdString(x));
	}

	for (int i = 1; i <= 31; i++)
	{
		stringstream ss;
		if (i < 10)
			ss << "0";
		ss << i;
		string x = ss.str();
		day->addItem(QString::fromStdString(x));
	}



	
	addReviewWindow->show();
}
void MainWindow::closeAddWindow()
{
	addReviewWindow->close();
}
void MainWindow::populateReviews()
{
	//remember to go year month day
	int dayEntered = day->currentIndex() + 1;
	int monthEntered = month->currentIndex() + 1;
	int yearEntered = year->currentIndex() + 1970;

	//date
	stringstream ss;
	ss << yearEntered << "-";
	if (monthEntered < 10) ss << "0" << monthEntered << "-";
	else ss << monthEntered << "-";

	if (dayEntered < 10) ss << "0" << dayEntered << "-";
	else ss << dayEntered;

	string tempDate = ss.str();

	//prodName
	int currIndex = searchResults->currentRow();
	Product* p = hits[currIndex];
	string tempProductName = p->getName();

	//rating
	int tempRating = reviewRating->currentIndex() + 1;

	//username
	string tempUser = selectUser->currentText().toStdString();

	//actual review
	string tempReview = reviewText->toPlainText().toStdString();;

	Review* r = new Review;
    r->prodName = tempProductName;
    r->rating = tempRating;
    r->username = tempUser;
    r->date = tempDate;
    r->reviewText = tempReview;

    mds->addReview(r);

}