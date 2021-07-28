/***********************************************************
** ISTANBUL MEDIPOL UNIVERSITY                            **
** SCHOOL OF ENGINEERING AND NATURAL SCIENCES             **
** COMPUTER ENGINEERING                                   **
** PROGRAMMING FOR ENGINEERING                            **
**                                                        **
** FATİH FURKAN AK - 64170032                             **
** ÖMER SALİH DENİZ - 64170036                            **
** İBRAHİM TALHA ASAN - 64170019                          **
***********************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

// ToLine function that makes write operations to file
class Entity {
    virtual string ToLine();
};

string Entity::ToLine() {
    return string();
}

// Variables to be written to the product.txt
class Product : public Entity {
public:
    string PK_productID;
    string productName;
    string stock;
    string unitPrice;
    string brandName;
    string deletedProductID;
    string ToLine() {
        return this->PK_productID + ' ' + this->productName + ' ' + this->stock + ' ' + this->unitPrice + ' ' + this->brandName + '\n';
    }
};

// Variables to be written to the Project.txt
class Project : public Entity {
public:
    string PK_projectID;
    string projectName;
    string subcontractor;
    string projectManager;
    string projectController;
    string deletedProductID;
    string projectCost;
    string ToLine() {
        return this->PK_projectID + ' ' + this->projectName + ' ' + this->subcontractor + ' ' + this->projectManager + ' ' + this->projectController +  ' ' + this->projectCost + '\n';
    }
};

// Variables to be written to the ProfitSharing.txt
class ProfitSharing : public Entity {
public:
    string FK_projectID;
    string profitSharingPeriod;
    string FK_productID;
    string PK_profitSharingID;
    string profitSharingRate;
    string ToLine() {
        return this->FK_projectID + ' ' + this->profitSharingPeriod + ' ' + this->FK_productID + ' ' + this->PK_profitSharingID + ' ' + this->profitSharingRate + '\n';
    }
};

// Arrays for profit sharings, products and projects
ProfitSharing profitSharingTxt[1000];
Product productTxt[1000];
Project projectTxt[1000];

// Type definitions were made using the enum structure and action was taken according to the incoming type
enum Type {
    productType,
    projectType,
    profitSharingType
};

// Add fuction
void Add(Type type) {
    ofstream writeFile;
    Product tmpProduct;
    Project tmpProject;
    ProfitSharing tmpProfitSharing;
    char answer;
    switch (type)
    {
        case productType:
            // Product Adding Process
            writeFile.open("Product.txt", ios::app);
            do {
                cout << "\nProduct ID: "; cin >> tmpProduct.PK_productID;
                cout << "\nProduct Name: "; cin >> tmpProduct.productName;
                cout << "\nProduct Stock: "; cin >> tmpProduct.stock;
                cout << "\nProduct Unit Price: "; cin >> tmpProduct.unitPrice;
                cout << "\nProduct Brand: "; cin >> tmpProduct.brandName;

                writeFile << tmpProduct.ToLine();

                cout << "\n Do you want to make another product registration? (y/n)"; cin >> answer;
            } while (!(answer == 'n'));
            writeFile.close();
            cout << "The product has been successfully registered." << endl;
            break;

        case projectType:
            // Project Adding Process
            writeFile.open("Project.txt", ios::app);
            do {
                cout << "\nProject ID: "; cin >> tmpProject.PK_projectID;
                cout << "\nProject Name: "; cin >> tmpProject.projectName;
                cout << "\nProject Subcontractor: "; cin >> tmpProject.subcontractor;
                cout << "\nProject Manager: "; cin >> tmpProject.projectManager;
                cout << "\nProject Controller: "; cin >> tmpProject.projectController;
                cout << "\nProject Cost: "; cin >> tmpProject.projectCost;
                writeFile << tmpProject.ToLine();

                cout << "\n Do you want to make another project registration? (y/n)"; cin >> answer;
            } while (!(answer == 'n'));
            writeFile.close();
            cout << "The project has been successfully registered." << endl;
            break;

        case profitSharingType:
            // Profit Sharing Adding Process
            writeFile.open("ProfitSharing.txt", ios::app);
            do {
                cout << "\nProject ID: "; cin >> tmpProfitSharing.FK_projectID;
                cout << "\nProfit Sharing Period: "; cin >> tmpProfitSharing.profitSharingPeriod;
                //cout << "\nProduct Used: "; cin >> tmpProfitSharing.FK_productID;
                cout << "\nProfit Sharing Rate: "; cin >> tmpProfitSharing.profitSharingRate;
                writeFile << tmpProfitSharing.ToLine();

                cout << "\n Do you want to make another profit sharing registration? (y/n)"; cin >> answer;
            } while (!(answer == 'n'));
            writeFile.close();
            cout << "The profit sharing has been successfully registered." << endl;
            break;
    }
}

// Silme fonksiyonu
void Delete(Type type) {
    ifstream readFile("Product.txt");
    ofstream writeFile("temp1.txt");
    ifstream readFile2("Project.txt");
    ofstream writeFile2("temp2.txt");
    ifstream readFile3("ProfitSharing.txt");
    ofstream writeFile3("temp3.txt");
    Product tmpProduct;
    Project tmpProject;
    ProfitSharing tmpProfitSharing;
    char answer;
    switch (type)
    {
        case productType:
            // Product Deleting Process
            cout << "\n ID of the product you want to delete: ";
            cin >> tmpProduct.deletedProductID;

            while (readFile >> tmpProduct.PK_productID >> tmpProduct.productName >> tmpProduct.stock >> tmpProduct.unitPrice >> tmpProduct.brandName)
            {
                // If the entered product ID is in the records
                if (tmpProduct.PK_productID == tmpProduct.deletedProductID)
                {
                    // If there is a product that satisfies the condition, it displays it on the screen
                    cout << "=== Product Informations ===" << endl << endl;
                    cout << "Product ID: " << tmpProduct.deletedProductID << endl;
                    cout << "Product Name: " << tmpProduct.productName << endl;
                    cout << "Product Stock: " << tmpProduct.stock << endl;
                    cout << "Product Unit Price: " << tmpProduct.unitPrice << endl;
                    cout << "Product Brand: " << tmpProduct.brandName << endl;

                    cout << "The product has been successfully deleted." << endl;
                }
                else
                {
                    writeFile << tmpProduct.ToLine();
                    writeFile3 << tmpProfitSharing.ToLine();
                }
            }

            writeFile.close();
            readFile.close();
            writeFile3.close();
            readFile3.close();

            remove("Product.txt");
            rename("temp1.txt", "Product.txt");
            remove("ProfitSharing.txt");
            rename("temp3.txt", "ProfitSharing.txt");

            break;

        case projectType:
            // Project Deleting Process
            cout << "\n ID of the project you want to delete: ";
            cin >> tmpProject.deletedProductID;

            while (readFile2 >> tmpProject.PK_projectID >> tmpProject.projectName >> tmpProject.subcontractor >> tmpProject.projectManager >> tmpProject.projectController >> tmpProject.projectCost)
            {
                // If the entered project ID is in the records
                if (tmpProject.PK_projectID == tmpProject.deletedProductID && tmpProfitSharing.FK_projectID != tmpProject.PK_projectID)
                {
                    // If there is a project that satisfies the condition, it displays it on the screen
                    cout << "\n=== Project Informations ===" << endl << endl;
                    cout << "Project ID: " << tmpProject.deletedProductID << endl;
                    cout << "Project Name: " << tmpProject.projectName << endl;
                    cout << "Project Subcontractor: " << tmpProject.subcontractor << endl;
                    cout << "Project Manager: " << tmpProject.projectManager << endl;
                    cout << "Project Controller: " << tmpProject.projectController << endl;
                    cout << "Project Cost: " << tmpProject.projectCost << endl;
                    cout << "The project has been successfully deleted." << endl;
                }
                else
                {
                    writeFile2 << tmpProject.ToLine();
                }
            }
            writeFile2.close();
            readFile2.close();
            remove("Project.txt");
            rename("temp2.txt", "Project.txt");
            break;
    }
}

// Search fuction
void Search(Type type) {
    Product tmpProduct;
    Project tmpProject;
    ProfitSharing tmpProfitSharing;
    string searchItem;
    char answer;
    ifstream readFile("Product.txt");
    ifstream readFile2("Project.txt");
    ifstream readFile3("ProfitSharing.txt");
    int i = 0;

    switch (type)
    {
        case productType:
            // Product Search Process
            cout << "ID of the product you want to search: "; cin >> searchItem;
            while (!readFile.eof())
            {
                readFile >> tmpProduct.PK_productID >> tmpProduct.productName >> tmpProduct.stock >> tmpProduct.unitPrice >> tmpProduct.brandName ;
                productTxt[i] = tmpProduct;
                if (searchItem == tmpProduct.PK_productID)
                {
                    cout << "\n=== Product Informations ===\n";
                    cout << "Product ID: " << tmpProduct.PK_productID << endl;
                    cout << "Product Name: " << tmpProduct.productName << endl;
                    cout << "Product Stock: " << tmpProduct.stock << endl;
                    cout << "Product Unit Price: " << tmpProduct.unitPrice << endl;
                    cout << "Brand Name: " << tmpProduct.brandName << endl;
                    readFile.close();
                    break;
                }
                i++;
            }
            break;

        case projectType:
            // Project Search Process
            cout << "ID of the project you want to search: "; cin >> searchItem;
            while (!readFile2.eof())
            {
                readFile2 >> tmpProject.PK_projectID >> tmpProject.projectName
                          >> tmpProject.subcontractor >> tmpProject.projectManager
                          >> tmpProject.projectController >> tmpProject.projectCost;
                projectTxt[i] = tmpProject;
                if (searchItem == tmpProject.PK_projectID)
                {
                    cout << "\n=== Project Informations ===\n";
                    cout << "Project ID: " << tmpProject.PK_projectID << endl;
                    cout << "Project Name: " << tmpProject.projectName << endl;
                    cout << "Project Subcontractor: " << tmpProject.subcontractor << endl;
                    cout << "Project Manager: " << tmpProject.projectManager << endl;
                    cout << "Project Controller: " << tmpProject.projectController << endl;
                    cout << "Project Cost: " << tmpProject.projectCost << endl;
                    readFile2.close();
                    break;
                }
                i++;
            }
            break;
    }
}

// Report function
void Report(Type type) {
    Product tmpProduct;
    Project tmpProject;
    ProfitSharing tmpProfitSharing;
    ifstream readFile1;
    ifstream readFile2;
    ifstream readFile3;
    char answer;
    int i = 0;
    int j = 0;
    int total = 0;

    switch (type)
    {
        case productType:
            // Product Reporting Process
            readFile1.open("Product.txt", ios::in);
            cout << "\n=== Report of All Products === \n";
            while (readFile1 >> tmpProduct.PK_productID >> tmpProduct.productName >>
                             tmpProduct.stock >> tmpProduct.unitPrice >> tmpProduct.brandName )
            {
                if (tmpProduct.PK_productID != "")
                {
                    productTxt[j] = tmpProduct;

                    cout << "Product ID: " << tmpProduct.PK_productID << endl;
                    cout << "Product Name: " << tmpProduct.productName << endl;
                    cout << "Product Stock: " << tmpProduct.stock << endl;
                    cout << "Product Unit Price: " << tmpProduct.unitPrice << endl;
                    cout << "Product Brand: " << tmpProduct.brandName << endl;
                    cout << endl;
                }
                j++;
            }
            readFile1.close();
            break;


        case projectType:
            // Project Reporting Process
            readFile2.open("Project.txt", ios::in);
            cout << "\n=== Report of All Projects ===\n";
            while (readFile2 >> tmpProject.PK_projectID >> tmpProject.projectName
                             >> tmpProject.subcontractor >> tmpProject.projectManager
                             >> tmpProject.projectController >> tmpProject.projectCost)
            {
                projectTxt[i] = tmpProject;

                cout << "Project ID: " << tmpProject.PK_projectID << endl;
                cout << "Project Name: " << tmpProject.projectName << endl;
                cout << "Project Subcontractor: " << tmpProject.subcontractor << endl;
                cout << "Project Manager: " << tmpProject.projectManager << endl;
                cout << "Project Controller: " << tmpProject.projectController << endl;
                cout << "Project Cost: " << tmpProject.projectCost << endl;
                cout << endl;
                i++;
            }
            readFile2.close();
            break;


        case profitSharingType:
            // Profit Sharing Reporting Process
            readFile3.open("ProfitSharing.txt", ios::in);
            readFile2.open("Project.txt", ios::in);

            cout << "\n=== Report of All Profit Sharings ===\n";

            i = 0;
            j = 0;

            while (readFile3 >> tmpProfitSharing.FK_projectID >>
                             tmpProfitSharing.profitSharingPeriod >> tmpProfitSharing.profitSharingRate &&
                   readFile2 >> tmpProject.PK_projectID >> tmpProject.projectName
                             >> tmpProject.subcontractor >> tmpProject.projectManager
                             >> tmpProject.projectController >> tmpProject.projectCost)
            {
                profitSharingTxt[i] = tmpProfitSharing;
                projectTxt[j] = tmpProject;

                cout << "\n Project ID: " << tmpProfitSharing.FK_projectID << endl;
                cout << "Profit Sharing Period: " << tmpProfitSharing.profitSharingPeriod << endl;
                cout << "Profit Sharing Income: " << stoi(tmpProject.projectCost) * (stoi(tmpProfitSharing.profitSharingRate) / 100.0) << endl;
                cout << "Profit Sharing Rate: " << tmpProfitSharing.profitSharingRate << endl;

                i++;
            }

            readFile3.close();
            break;
    }
    i = 0;
}


int main() {

    Type type;
    int choice;
    char answer = 'y';

    // Main Menu
    do {
        cout << "\n\nWhat would you like to do?" << endl << endl;
        cout << "1) Add Product" << endl;
        cout << "2) Delete Product" << endl;
        cout << "3) Search Product" << endl;
        cout << "4) Report of All Products" << endl;

        cout << "\n*********************************\n";

        cout << "\n5) Add Project" << endl;
        cout << "6) Delete Project" << endl;
        cout << "7) Search Project" << endl;
        cout << "8) Report of All Projects" << endl;

        cout << "\n*********************************\n";

        cout << "\n9) Add Profit Sharing" << endl;
        cout << "10) Report of All Profit Sharings" << endl;

        cout << "\n*********************************\n";

        cout << "\n0) Exit" << endl;

        cin >> choice;

        if (choice == 0)
        {
            return 0;
        }

        if (choice == 1)
        {
            type = productType;
            Add(type);
        }

        if (choice == 2)
        {
            type = productType;
            Delete(type);
        }

        if (choice == 3)
        {
            type = productType;
            Search(type);
        }

        if (choice == 4)
        {
            type = productType;
            Report(type);
        }

        if (choice == 5)
        {
            type = projectType;
            Add(type);
        }

        if (choice == 6)
        {
            type = projectType;
            Delete(type);
        }

        if (choice == 7)
        {
            type = projectType;
            Search(type);
        }

        if (choice == 8)
        {
            type = projectType;
            Report(type);
        }

        if (choice == 9)
        {
            type = profitSharingType;
            Add(type);
        }


        if (choice == 10)
        {
            type = profitSharingType;
            Report(type);
        }
    }
    while (choice != 11);
}