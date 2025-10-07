/****************************************************
* Course: CS213
* Assignment : A1 - Part 1
*
*Section : X
*
*Team Members :
*1. Mohamed Jamal Mohamed - ID : 20242274
* 2. Ahmed Osama Sediq - ID : 20242004
* 3. Mazen Magdy Fouad - ID : 20240449
*
*Description :
    *-Mohamed Jamal implemented :
**InvertImage
* *RotateImage
*
*-Ahmed Osama implemented :
**FlipImage
* *BlackAndWhite
*
*-Mazen Magdy implemented :
**GrayScale
* *DarkenAndLighten
*
*-The Menu was implemented by :
**Ahmed Osama
* *Mohamed Jamal
* *Mazen Magdy
*
****************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <cstdlib>
#include "Image_Class.h"
using  namespace std;

enum enfilters {
    enLoadImage = 1, enGrayScale = 2, enBlackAndWhite = 3, enInvertImage = 4,
    enFlipImage = 5, enDarkenAndLighten = 6, enRotateImage = 7, enSaveImage = 8,
    enExit = 9
};

// ==================++ Declaration Filter ++=====================

enfilters ShowMenuScreen();
int MenuScreenAndOperatAFilter(vector<pair<Image, string>>& vCurrentPicAndItsName);
void StartFilterProgram(vector<pair<Image, string>>& vCurrentPicAndItsName);

// ==================++ General helpful functions and messages ++=====================

void ClearScreen() {
    system("cls");
}

void GenerateHeader(int NumOfUnderScores, string title) {
    //This function Generates a header and Take i title and put it in the middle
    ClearScreen();
    string line(NumOfUnderScores, '_');
    cout << line << '\n';
    int Size = title.size();
    int NumofSpaces = (NumOfUnderScores - Size) / 2;
    cout << string(NumofSpaces, ' ') << title << '\n';
    cout << line << '\n';
}

void SuccessSound() {
    Beep(1000, 200);
    Beep(1500, 200);
}

void AnotherSound() {
    Beep(1000, 200);
    Beep(1500, 700);
}

void ShowEnd(int NumOfUnderScore) {
    cout << "\nThe process is done successfully :)\n";
    cout << "Please press any key to go  to main menu....\n";
    for (int i = 0; i < NumOfUnderScore; i++) cout << '_';
    cout << "\n>";
    SuccessSound();
    system("pause>0");
}

int GenerateOptionsListAndChoose(vector <string>& options, int NumOfUnderScores) {
    cout << "Please choose one of this options by enter the choice number..\n";
    cout << string(NumOfUnderScores, '_') << '\n';
    int size = options.size();
    for (int i = 0; i < size; i++) {
        cout << '[' << i + 1 << "] " << options[i] << '\n';
    }
    cout << string(NumOfUnderScores, '_') << '\n';
    cout << '>';
    int num; cin >> num;
    return num;
}

// ==================++ Validation Functions And Messages ++=====================

bool IsExtensionFalse(string FileName) {
    int i = 0;
    while (FileName[i] != '.' && i != FileName.size() - 1)  i++;
    if (i == FileName.size() - 1) return true;

    string temp = "";
    for (int j = ++i; j < FileName.size(); j++) temp += FileName[j];

    if (temp != "jpg" && temp != "bmp" && temp != "png" && temp != "tga") return true;
    return false;
}

bool CheakIfThereArentCurrnetPic(vector<pair<Image, string>>& CurrentPicAndItsName) {
    if (CurrentPicAndItsName.empty()) return true;

    return false;
}

void ThereIsNoPicMessage() {
    cout << "\nError )-:, you must load an image at first to use filters\n";
    cout << "Please press any key to go back to main menu then upload an image....\n";
    cout << "\a";
    cout << ">";
    system("pause>0");
}

void UnValidNumberMessage(int from, int to) {
    cout << "\nError )-:, you should enter a number between [" << from << " : " << to << "]\n";
    cout << "Please press any key to go back to last menu and enter valid number....\n";
    cout << "\a";
    cout << ">";
    system("pause>0");
}

void PuttyEndingMessage() {
    ClearScreen();
    cout << "\t _______________________________________________________________\n";
    cout << "\t|    See you soon in our Baby photoshop program ya habibi :-)   |\n";
    cout << "\t|_______________________________________________________________|\n";
    cout << "\t         | Please give us full marks, dear doctor <3 |\n";
    cout << "\t         |___________________________________________|\n";
}

// ==================++ Flip Filter ++=====================

void VerticalFlip(Image& image) {
    unsigned int totalCols = image.height - 1;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height / 2; j++) {
            for (int RGB = 0; RGB < 3; RGB++) {
                swap(image(i, j, RGB), image(i, totalCols - j, RGB));
            }
        }
    }
    ShowEnd(65);
    // Flip image vertically by swapping rows
}

void HorizontalFlip(Image& image) {
    unsigned int totalRows = image.width - 1;
    for (int i = 0; i < image.width / 2; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int RGB = 0; RGB < 3; RGB++) {
                swap(image(i, j, RGB), image(totalRows - i, j, RGB));
            }
        }
    }
    ShowEnd(65);
    // Flip image horizontally by swapping column
}

void FlipImage(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    GenerateHeader(65, "Flip image screen");
    if (CheakIfThereArentCurrnetPic(vCurrentPicAndItsName)) {
        return void(ThereIsNoPicMessage());
    }
    vector<string> options = { "Flip image Horizontally (left-right flip)",
        "Flip image vertically (bottom-top flip)", "Back to menu" };
    int ChoiceNum = GenerateOptionsListAndChoose(options, 65);
    switch (ChoiceNum) {
    case 1: HorizontalFlip(vCurrentPicAndItsName[0].first); break; //first here is the opject (The current photo)
    case 2: VerticalFlip(vCurrentPicAndItsName[0].first); break;
    case 3: MenuScreenAndOperatAFilter(vCurrentPicAndItsName); break;
    default: UnValidNumberMessage(1, 3);
        FlipImage(vCurrentPicAndItsName);
    }
}

// ==================++ GrayScale Filter ++=====================

void Grayscale(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    GenerateHeader(60, "Grayscale filter screen");
    if (CheakIfThereArentCurrnetPic(vCurrentPicAndItsName)) {
        return void(ThereIsNoPicMessage());
    }
    Image image;
    image = vCurrentPicAndItsName[0].first;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int total = 0;
            for (int RGB = 0; RGB < 3; RGB++) {
                total += image(i, j, RGB);
            }
            total /= 3;
            for (int RGB = 0; RGB < 3; RGB++) {
                image(i, j, RGB) = total;
            }
        }
    }
    vCurrentPicAndItsName[0].first = image;
    ShowEnd(60);
}

// ==================++ BlackAndWhite Filter ++=====================

void BlackAndWhite(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    GenerateHeader(65, "Black and White filter screen");
    if (CheakIfThereArentCurrnetPic(vCurrentPicAndItsName)) {
        return void(ThereIsNoPicMessage());
    }
    for (int i = 0; i < vCurrentPicAndItsName[0].first.width; i++) {
        for (int j = 0; j < vCurrentPicAndItsName[0].first.height; j++) {
            unsigned int total = 0;
            for (int RGB = 0; RGB < 3; RGB++) {
                total += vCurrentPicAndItsName[0].first(i, j, RGB);
            }
            if (total <= 382) {
                vCurrentPicAndItsName[0].first.setPixel(i, j, 0, 0);
                vCurrentPicAndItsName[0].first.setPixel(i, j, 1, 0);
                vCurrentPicAndItsName[0].first.setPixel(i, j, 2, 0);
                continue;
            }
            vCurrentPicAndItsName[0].first.setPixel(i, j, 0, 255);
            vCurrentPicAndItsName[0].first.setPixel(i, j, 1, 255);
            vCurrentPicAndItsName[0].first.setPixel(i, j, 2, 255);
        }
    }
    ShowEnd(65);
}


// ==================++ LightenAndDarken Filter ++=====================

void DarkenAlgo(Image& img1, float LevelOfBrightness) {
    for (int i = 0; i < img1.width; i++) {
        for (int j = 0; j < img1.height; j++) {
            for (int RGB = 0; RGB < 3; RGB++) {
                img1(i, j, RGB) *= LevelOfBrightness;
            }
        }
    }
    ShowEnd(65);
}

void LightenAlgo(Image& image, float LevelOfBrightness) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int RGB = 0; RGB < 3; RGB++) {
                int val = image(i, j, RGB) * LevelOfBrightness;
                val = min(val, 255);
                image(i, j, RGB) = (val);
            }
        }
    }
    ShowEnd(65);
}

void DarkenLevel(Image& image) {
    ClearScreen();
    GenerateHeader(65, "Darken Levels screen");
    vector<string> options = {
        "25%", "50%", "75%", "100% Make completely black" };
    int ChoiceNum = GenerateOptionsListAndChoose(options, 65);
    switch (ChoiceNum) {
    case 1: DarkenAlgo(image, .75); break;
    case 2: DarkenAlgo(image, .5); break;
    case 3:  DarkenAlgo(image, .25); break;
    case 4: DarkenAlgo(image, 0); break;
    default: UnValidNumberMessage(1, 4); DarkenLevel(image);
    }
}

void LightenLevel(Image& image) {
    ClearScreen();
    GenerateHeader(65, "Lighten Levels screen");
    vector<string> options = { "25%", "50%", "75%", "100%" };
    int ChoiceNum = GenerateOptionsListAndChoose(options, 65);
    switch (ChoiceNum) {
    case 1: LightenAlgo(image, 1.25); break;
    case 2: LightenAlgo(image, 1.5); break;
    case 3:  LightenAlgo(image, 1.75); break;
    case 4: LightenAlgo(image, 2); break;
    default: UnValidNumberMessage(1, 4); LightenLevel(image);

    }
}

void DarkenAndLighten(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    GenerateHeader(65, "Darken and lighten screen");
    if (CheakIfThereArentCurrnetPic(vCurrentPicAndItsName)) {
        return void(ThereIsNoPicMessage());
    }
    vector<string> options = { "Darken filter", "Lighten filter", "Back to menu" };
    int ChoiceNum = GenerateOptionsListAndChoose(options, 65);
    switch (ChoiceNum) {
    case 1: DarkenLevel(vCurrentPicAndItsName[0].first); break;
    case 2: LightenLevel(vCurrentPicAndItsName[0].first); break;
    case 3: MenuScreenAndOperatAFilter(vCurrentPicAndItsName); break;
    default: UnValidNumberMessage(1, 3); DarkenAndLighten(vCurrentPicAndItsName);
    }
}

// =================== Rotate Filter =====================

void Rotate90DegreesAlgo(Image& image) {
    Image temp(image.height, image.width);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int RGB = 0; RGB < 3; ++RGB) {
                temp(image.height - j - 1, i, RGB) = image(i, j, RGB);
            }
        }
    }
    image = temp;
    ShowEnd(65);
}

void Rotate180DegreesAlgo(Image& image) {
    Image temp(image.width, image.height);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int RGB = 0; RGB < 3; ++RGB) {
                temp(image.width - i - 1, image.height - j - 1, RGB) = image(i, j, RGB);
            }
        }
    }
    image = temp;
    ShowEnd(65);
}

void Rotate270DegreesAlgo(Image& image) {
    Image temp(image.height, image.width);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int RGB = 0; RGB < 3; ++RGB) {
                temp(j, i, RGB) = image(image.width - i - 1, j, RGB);
            }
        }
    }
    image = temp;
    ShowEnd(65);
}

void RotateImage(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    GenerateHeader(65, "Rotate image screen");
    if (CheakIfThereArentCurrnetPic(vCurrentPicAndItsName)) {
        return void(ThereIsNoPicMessage());
    }
    vector<string> options = { "Rotate the image 90 degrees clockwise",
        "Rotate the image 180 degrees clockwise", "Rotate the image 270 degrees clockwise",
    "Back to menu" };
    int ChoiceNum = GenerateOptionsListAndChoose(options, 65);
    switch (ChoiceNum) {
    case 1: Rotate90DegreesAlgo(vCurrentPicAndItsName[0].first); break;
    case 2: Rotate180DegreesAlgo(vCurrentPicAndItsName[0].first); break;
    case 3: Rotate270DegreesAlgo(vCurrentPicAndItsName[0].first); break;
    case 4: MenuScreenAndOperatAFilter(vCurrentPicAndItsName);   break;
    default: UnValidNumberMessage(1, 4); RotateImage(vCurrentPicAndItsName);

    }
}

// ===================++ Invert Filters ++=====================

void InvertImage(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    GenerateHeader(65, "Invert image screen");
    if (CheakIfThereArentCurrnetPic(vCurrentPicAndItsName)) {
        return void(ThereIsNoPicMessage());
    }
    //vCurrentPic[0].first.width = image.width, becase the first of pair is Image (object)
    for (int i = 0; i < vCurrentPicAndItsName[0].first.width; ++i) {
        for (int j = 0; j < vCurrentPicAndItsName[0].first.height; ++j) {
            for (int RGB = 0; RGB < 3; ++RGB) {
                vCurrentPicAndItsName[0].first(i, j, RGB) =
                    255 - vCurrentPicAndItsName[0].first(i, j, RGB);
            }
        }
    }
    ShowEnd(65);
}


// ===================++ Save And Load Filters ++=====================

void EnterImagePairWithValidation(pair<Image, string>& pCurrentPicAndItsName) {

    if (cin.peek() == '\n')
        cin.ignore();

    bool success = false;
    while (!success)
    {
        getline(cin, pCurrentPicAndItsName.second);

        if (IsExtensionFalse(pCurrentPicAndItsName.second)) {
            cout << "\a";
            cout << "\nError )-:, Please enter a valid extension [.jpg, .bmp, .png, .tga]\n>";
            continue;
        }

        try {
            pCurrentPicAndItsName.first.loadNewImage(pCurrentPicAndItsName.second);
            success = true;
        }
        catch (...) {
            cout << "\a";
            cout << "\nError )-:, Please check if the input image exists and enter file name again\n>";
        }
    }
}
void SaveAnImage(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    GenerateHeader(65, "Save image screen");
    //Firstly Check if The Vector is Filled or not (There is currnet picture or not)
    if (!vCurrentPicAndItsName.empty()) {
        // if there is a current picture ask user if he wants to save it with the same name or with different name
        vector<string> options = { "Save with same name",
            "Save with different name", "Back to main menu" };
        int ChoiceNum = GenerateOptionsListAndChoose(options, 65);
        switch (ChoiceNum) {
        case 1: {
            // if he chose 1 then he wanna save it with the same name, so we save the current pair in the vec and clear it
            vCurrentPicAndItsName[0].first.saveImage(vCurrentPicAndItsName[0].second);// == image.saveImage(selected_image);

            ShowEnd(65);
            break;
        }
        case 2: {
            // if he chose 2 then he wanna save it with different name, so we should ask him to enter the new name
            cout << "\nPlease enter a new name for the edited image.\n";
            cout << "and specify extension [.jpg, .bmp, .png, .tga]: \n>";
            // here, to handle spaces we should firstly igonre the input and take the new name with getline(), and also
            // we need to check if the extension he entered is correct or not
            cin.ignore();
            getline(cin, vCurrentPicAndItsName[0].second);
            while (IsExtensionFalse(vCurrentPicAndItsName[0].second)) {
                cout << "\a\nError )-:, Please enter a valid extension [.jpg, .bmp, .png, .tga]\n>";
                getline(cin, vCurrentPicAndItsName[0].second);
            }

            // Then save it with the same object and the new name he enterd
            vCurrentPicAndItsName[0].first.saveImage(vCurrentPicAndItsName[0].second);// == image.saveImage(selected_image);

            ShowEnd(65); break;
        }
        case 3: MenuScreenAndOperatAFilter(vCurrentPicAndItsName); break; // If he chose 3 then he will back to menu

        default: UnValidNumberMessage(1, 3); SaveAnImage(vCurrentPicAndItsName); // if he chose any thing other than(1 : 3)
        }
    }
    else {
        // And here, if there is no image at the beginning at all
        cout << "\nError )-:, Please upload an image firstly then save it after editing\n";
        cout << "\aPlease press any key to go back to main menu then upload an image....\n>";
        system("pause>0");
    }
}

void LoadAnImage(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    GenerateHeader(65, "Load image screen");
    // we at first check if the vector is not empty (there is current image)
    if (!vCurrentPicAndItsName.empty()) {
        vector<string> options = { "Save current image",
            "Choose another image", "Back to main menu" };
        int ChoiceNum = GenerateOptionsListAndChoose(options, 65);

        // if he chose 1 then he wants to save the current image at first
        if (ChoiceNum == 1) {
            SaveAnImage(vCurrentPicAndItsName);
            return void();
        }
        // if he chose 3 then he wants to go to menu
        else if (ChoiceNum == 3) {
            MenuScreenAndOperatAFilter(vCurrentPicAndItsName);
            return void();
        }
        // if he chose any thing other than(1 : 3)
        else if (ChoiceNum < 1 || ChoiceNum > 3) {
            UnValidNumberMessage(1, 3);
            LoadAnImage(vCurrentPicAndItsName);
            return void();
        }
    }
    // There are only two cases to be here (if he pressed 2 when there is a image) / (if there is no currnet image)
    vCurrentPicAndItsName.clear();
    cout << "\nPlease enter new image with specify extension:  \n>";

    //I chose vector<pair<image, string>> because in some filters we will need to have more than one image
    // at the same time in one place, such as the image merging filter.
    pair<Image, string> PCurrentPicAndItsName; // first == image // second == filename
    //fill The pair by this function -> EnterTheImageName(), and push it in vector
    EnterImagePairWithValidation(PCurrentPicAndItsName);
    vCurrentPicAndItsName.push_back(PCurrentPicAndItsName);

    ShowEnd(65);
}

// ===================++ Menu screen functions ++=====================

int ShowMenuScreenAndTackChoice() {
    // This function will print main menu and take choice from our user
    GenerateHeader(65, "Main menu screen");
    vector<string> options = { "Load new image", "Grayscale filter","Black and white filter",
        "Invert image colors filter", "Flip image filter", "Brightness filter",
        "Rotate image filter", "Save current image", "Exit" };
    // We will take user choice by this function -> GenerateOptionsListAndChoose();
    int ChoiceNum = GenerateOptionsListAndChoose(options, 65);

    return ChoiceNum;
}

void Exit(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    ClearScreen();
    char confirmation;
    // First, we will check if there is a current image or not
    // If there is, we will ask the user to confirm the operation
    // Otherwise, the user should return to the menu, save it first, and then exit
    if (!CheakIfThereArentCurrnetPic(vCurrentPicAndItsName)) {
        cout << "Are you sure to exit the program ?\n";
        cout << "You didn't save the current image, and it will not be saved )-:\n";
        AnotherSound();
        cout << "To exit please confirm and press [Y] or press [N] to go back to menu\n";
        cout << ">";
        while (true) {
            cin >> confirmation;
            if (confirmation == 'Y' || confirmation == 'y') {
                PuttyEndingMessage();
                return;
            }
            else if (confirmation == 'n' || confirmation == 'N') {
                StartFilterProgram(vCurrentPicAndItsName);
                return;
            }

            else {

                cout << "\nPlease enter [Y/N]\n";
                cout << ">";
            }
        }
    }
    else
        PuttyEndingMessage();

}

int MenuScreenAndOperatAFilter(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    int ChoiceNum = ShowMenuScreenAndTackChoice();

    switch (ChoiceNum) {
    case enfilters::enLoadImage: LoadAnImage(vCurrentPicAndItsName); break;
    case enfilters::enFlipImage: FlipImage(vCurrentPicAndItsName); break;
    case enfilters::enGrayScale: Grayscale(vCurrentPicAndItsName); break;
    case enfilters::enInvertImage: InvertImage(vCurrentPicAndItsName); break;
    case enfilters::enRotateImage: RotateImage(vCurrentPicAndItsName); break;
    case enfilters::enBlackAndWhite: BlackAndWhite(vCurrentPicAndItsName); break;
    case enfilters::enDarkenAndLighten: DarkenAndLighten(vCurrentPicAndItsName); break;
    case enfilters::enSaveImage: SaveAnImage(vCurrentPicAndItsName); break;
    case enfilters::enExit: return 9;
    default: UnValidNumberMessage(1, 9);
        MenuScreenAndOperatAFilter(vCurrentPicAndItsName);
    }
    return ChoiceNum;
}

void StartFilterProgram(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    int Choice;
    ClearScreen();

    do { Choice = MenuScreenAndOperatAFilter(vCurrentPicAndItsName); } while (Choice != 9);

    Exit(vCurrentPicAndItsName);
}

// ===================++ Main ++=====================

int main()
{
    vector<pair<Image, string>> vCurrentPicAndItsName;
    LoadAnImage(vCurrentPicAndItsName);
    StartFilterProgram(vCurrentPicAndItsName);
    system("pause>0");

    return 0;
}