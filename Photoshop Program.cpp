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
#include <stack>
#include <string>
#include <windows.h>
#include <cstdlib>
#include "Image_Class.h"
using  namespace std;

enum enfilters {
    enLoadImage = 1, enGrayScale = 2, enBlackAndWhite = 3, enInvertImage = 4,
    enFlipImage = 5, enDarkenAndLighten = 6, enRotateImage = 7, enCropImage, enResize = 9, enMerge = 10,
    enSaveImage = 11, enAppliedFiltersScreen = 12, enExit = 13
    
};

struct stCropFilterData {
    int x, y, width, height;
};

stack<Image>stFiltersHistory;
vector<string> vAppliedFilters;

// ==================++ Declaration Filter ++=====================

enfilters ShowMenuScreen();
int MenuScreenAndOperatAFilter(vector<pair<Image, string>>& vCurrentPicAndItsName);
void StartFilterProgram(vector<pair<Image, string>>& vCurrentPicAndItsName);
void FiltersHistory(vector<pair<Image, string>>& vCurrentPicAndItsName);
void EnterImageDataWithValidation(Image& image, string& filename);

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
    cout << "Please press any key to go to main menu....\n";
    for (int i = 0; i < NumOfUnderScore; i++) cout << '_';
    cout << "\n>";
    SuccessSound();
    system("pause>0");
}

void ShowEndInAppliedScreen(int NumOfUnderScore) {
    cout << "\nThe process is done successfully :)\n";
    cout << "Please press any key to go to applied filters screen....\n";
    for (int i = 0; i < NumOfUnderScore; i++) cout << '_';
    cout << "\n>";
    SuccessSound();
    system("pause>0");
}

int GenerateOptionsListAndChoose(const vector <string>& options, int NumOfUnderScores) {
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

int AppliedFiltersScreen(int NumOfUnderScores, vector<pair<Image, string>>& vCurrentPicAndItsName) {
    ClearScreen();
    GenerateHeader(NumOfUnderScores, "Applied Filter Screen");

    if (!vAppliedFilters.empty())
    {
        cout << "Currnet Image: " << vCurrentPicAndItsName[0].second << '\n';
        cout << string(NumOfUnderScores, '_') << '\n';
        string title = "|       Applied Filters       |";
        int NumOfSpaces = (NumOfUnderScores - title.size()) / 2;
        cout << string(NumOfSpaces, ' ') << title << '\n';
        cout << string(NumOfSpaces, ' ');  cout << "|_____________________________|\n\n";
        for (int i = 0; i < vAppliedFilters.size(); i++) {
            cout << '[' << i + 1 << "] " << vAppliedFilters[i] << '\n';
        }
    }
    else {
        cout << "\aThere are no filters applied to the image yet )-:\n\n";
        cout << "Please press any key to go back to main menu....\n";
        cout << string(NumOfUnderScores, '_') << '\n';
        cout << '>';
        system("pause>0");
        MenuScreenAndOperatAFilter(vCurrentPicAndItsName);
        return 0;
    }

    cout << string(NumOfUnderScores, '_') << '\n';
    cout << "[1] Clear Image\t    [2] Undo\t      [3] Back to menu\n\n>";
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

bool CheakIfThereArentCurrnetPic(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    if (vCurrentPicAndItsName.empty()) return true;

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
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Vertical flip");

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
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Horizontal flip");

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
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Gray Scale");

    vCurrentPicAndItsName[0].first = image;
    ShowEnd(60);
}

// ==================++ BlackAndWhite Filter ++=====================

void BlackAndWhite(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    GenerateHeader(65, "Black and White filter screen");
    if (CheakIfThereArentCurrnetPic(vCurrentPicAndItsName)) {
        return void(ThereIsNoPicMessage());
    }
    Image image;
    image = vCurrentPicAndItsName[0].first;
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned int total = 0;
            for (int RGB = 0; RGB < 3; RGB++) {
                total += image(i, j, RGB);
            }
            if (total <= 382) {
                image.setPixel(i, j, 0, 0);
                image.setPixel(i, j, 1, 0);
                image.setPixel(i, j, 2, 0);
                continue;
            }
            image.setPixel(i, j, 0, 255);
            image.setPixel(i, j, 1, 255);
            image.setPixel(i, j, 2, 255);
        }
    }
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Black And White");

    vCurrentPicAndItsName[0].first = image;
    ShowEnd(65);
}

// ==================++ LightenAndDarken Filter ++=====================

void LightenAndDarkenAlgo(Image& image, float LevelOfBrightness, bool IsLighten) {

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int RGB = 0; RGB < 3; RGB++) {
                int val = image(i, j, RGB) * LevelOfBrightness;
                val = min(val, 255);
                image(i, j, RGB) = (val);
            }
        }
    }
    stFiltersHistory.push(image);
    if (IsLighten) vAppliedFilters.push_back("Lighten filter");
    else vAppliedFilters.push_back("Darken filter");

    ShowEnd(65);
}

void DarkenLevel(Image& image) {
    ClearScreen();
    GenerateHeader(65, "Darken Levels screen");
    vector<string> options = {
        "25%", "50%", "75%", "100% Make completely black" };
    int ChoiceNum = GenerateOptionsListAndChoose(options, 65);
    switch (ChoiceNum) {
    case 1: LightenAndDarkenAlgo(image, .75, false); break;
    case 2: LightenAndDarkenAlgo(image, .5, false); break;
    case 3:  LightenAndDarkenAlgo(image, .25, false); break;
    case 4: LightenAndDarkenAlgo(image, 0, false); break;
    default: UnValidNumberMessage(1, 4); DarkenLevel(image);
    }
}

void LightenLevel(Image& image) {
    ClearScreen();
    GenerateHeader(65, "Lighten Levels screen");
    vector<string> options = { "25%", "50%", "75%", "100%" };
    int ChoiceNum = GenerateOptionsListAndChoose(options, 65);
    switch (ChoiceNum) {
    case 1: LightenAndDarkenAlgo(image, 1.25, true); break;
    case 2: LightenAndDarkenAlgo(image, 1.5, true); break;
    case 3:  LightenAndDarkenAlgo(image, 1.75, true); break;
    case 4: LightenAndDarkenAlgo(image, 2, true); break;
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
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Rotate (90) degree clockwise");

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
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Rotate (180) degree clockwise");

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
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Rotate (270) degree clockwise");

    ShowEnd(65);
}

void RotateImage(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    GenerateHeader(65, "Rotate image screen");
    if (CheakIfThereArentCurrnetPic(vCurrentPicAndItsName)) {
        return void(ThereIsNoPicMessage());
    }
    vector<string> options = { "Rotate the image 90 degree clockwise",
        "Rotate the image 180 degree clockwise", "Rotate the image 270 degree clockwise",
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
    Image image;
    image = vCurrentPicAndItsName[0].first;
    //vCurrentPic[0].first.width = image.width, becase the first of pair is Image (object)
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int RGB = 0; RGB < 3; ++RGB) {
                image(i, j, RGB) =
                    255 - image(i, j, RGB);
            }
        }
    }
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Invert Colors Filter");

    vCurrentPicAndItsName[0].first = image;
    ShowEnd(65);
}

//=================== ++Crop Filter++==================== =

stCropFilterData CropImageScreen() {

    GenerateHeader(70, "Crop image screen");
    stCropFilterData data;

    cout << "Please enter upper left corner point first(the starting point X, Y)\n";
    cout << '>'; cin >> data.x; cout << ">"; cin >> data.y; 
    cout << string(70, '_') << '\n';
    cout << "Please enter the width and height of the part you wanna crop\n>";
    cin >> data.width; cout << ">"; cin >> data.height;

    return data;
}

void ValidCropSize(stCropFilterData& data, Image& image) {

    while (data.x + data.width > image.width || data.y + data.height > image.height ||
        data.x < 0 || data.y < 0 || data.width <= 0 || data.height <= 0) {

        cout << "\n\aError )-:, you will be out of the bounds of the image\n";
        cout << "please enter new dimensions:\n";
        cout << "x -> ";
        cin >> data.x;
        cout << "\ny -> ";
        cin >> data.y;
        cout << "\nWidth -> ";
        cin >> data.width;
        cout << "\nHeight -> ";
        cin >> data.height;
        cout << '\n';
    }

}

void CropImageAlgo(stCropFilterData& data, Image& image) {
    Image CroppedImage(data.width, data.height);

    for (int i = data.x; i < data.x + data.width; i++) {
        for (int j = data.y; j < data.y + data.height; j++) {
            for (int RGB = 0; RGB < 3; RGB++) {                 
                CroppedImage(i - data.x, j - data.y, RGB) = image(i, j, RGB);
            }
        }
    }
    image = CroppedImage;
}

void CropImage(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    stCropFilterData data = CropImageScreen();
    ValidCropSize(data, vCurrentPicAndItsName[0].first);
    CropImageAlgo(data, vCurrentPicAndItsName[0].first);
    stFiltersHistory.push(vCurrentPicAndItsName[0].first);
    vAppliedFilters.push_back("Crop image");
    ShowEnd(70);
}
    
// ===================++ Ressize filter ++=====================

void ResizeAlgo(Image& image, int NewWidth, int Newheight) {

    int oldWidth = image.width, oldHeight = image.height; float xScale, yScale;
  
    if (oldWidth == NewWidth && oldHeight == Newheight)  return;

    xScale = (float)oldWidth / NewWidth;
    yScale = (float)oldHeight / Newheight;
    Image newImage(NewWidth, Newheight);

    for (int i = 0; i < NewWidth; i++) {
        for (int j = 0; j < Newheight; j++) {
            float TempI = round((i + 1) * xScale) - 1, Tempj = round((j + 1) * yScale) - 1;
            // validation
            TempI = max(0.0f, TempI); TempI = min(oldWidth - 1, TempI);
            Tempj = max(0.0f, Tempj); Tempj = min(oldHeight - 1, Tempj);
            for (int RGB = 0; RGB < 3; RGB++) {
                newImage(i, j, RGB) = image((int)TempI, (int)Tempj, RGB);
            }
        }
    }

    image = newImage;
}

float RatioMessageAndScalePercentage(bool IsReduction) {

    float ratio = 1.0;
    cout << "\nPlease enter a number between 1 and 100 (It expresses a ratio)\n";
    do {
        cin >> ratio;
        if (ratio < 1 || ratio > 100)
            cout << "\aError )-:, Please enter a number between 1 and 100\n";
    } while (ratio < 1 || ratio > 100);
    
    if (IsReduction) ratio *= -1;
    return (ratio / 100.0);
}

void RatioAlgoAndinterface(Image &image) {

    GenerateHeader(65, "Ratio entry screen");
    vector<string> options = { "Reduction" , "Increse" };
    int ChoiceNum = GenerateOptionsListAndChoose(options, 65);
    float ratio = 0.0;

    if (ChoiceNum == 1) {
        ratio = RatioMessageAndScalePercentage(true);
    }
    else if (ChoiceNum == 2) {
        ratio = RatioMessageAndScalePercentage(false);
    }
    else {
        UnValidNumberMessage(1, 2); RatioAlgoAndinterface(image); 
        return;
    }

    // if he choosed 100 in reduction the image will disappear so we check here first
    int width = max(1, (int) round( image.width + image.width * ratio) ); 
    int height = max(1, (int) round( image.height + image.height * ratio) );

    ResizeAlgo(image, width, height); 

}

void ResizeScreen(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    
    Image& image = vCurrentPicAndItsName[0].first;
    GenerateHeader(65, "Resize image screen");
    vector<string> options = { "enter new dimensions" , "enter a ratio of reduction or increase" , "Back to menu"};

    int ChoiceNum = GenerateOptionsListAndChoose(options, 65); bool ReturnedToMenu = false;

    switch (ChoiceNum) {
    case 1:
    {
        GenerateHeader(65, "New dimensions entry screen");
        int width, height; cout << "\nPlease enter new dimensions (New width and height)\n>"; 
        cin >> width; cout << ">"; cin >> height;

        ResizeAlgo(image, width, height); break; 
    }
    case 2:  RatioAlgoAndinterface(image); break;
    case 3:  MenuScreenAndOperatAFilter(vCurrentPicAndItsName); ReturnedToMenu = true;  break;
    default: UnValidNumberMessage(1, 3); ResizeScreen(vCurrentPicAndItsName);
    }

    if (!ReturnedToMenu) {
        stFiltersHistory.push(image);
        vAppliedFilters.push_back("Resize image");
        ShowEnd(65);
    }
}

// ===================++ Merge filter ++=====================

void MergeAlgo(Image& image, Image& image2) {

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int RGB = 0; RGB < 3; RGB++) {
                image(i, j, RGB) = (image2(i, j, RGB) + image(i, j, RGB)) / 2;
            }
        }
    }
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Merge images screen");
    ShowEnd(65);
}

void MergeCommonArea(Image& image, Image& image2) {
    int commonW = min(image.width, image2.width);
    int commonH = min(image.height, image2.height);
    stCropFilterData data, data2;

    data.x = (image.width - commonW) / 2;
    data.y = (image.height - commonH) / 2;
    data.width = commonW;
    data.height = commonH;

    data2.x = (image2.width - commonW) / 2;
    data2.y = (image2.height - commonH) / 2;
    data2.width = commonW;
    data2.height = commonH;

    CropImageAlgo(data, image);
    CropImageAlgo(data2, image2);
    MergeAlgo(image, image2);

}

void ResizeMerge(Image& image, Image& image2) {
    int maxW = max(image.width, image2.width);
    int maxH = max(image.height, image2.height);
    ResizeAlgo(image, maxW, maxH);
    ResizeAlgo(image2, maxW, maxH);
    MergeAlgo(image, image2);
}

void MergeImages(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    Image& image = vCurrentPicAndItsName[0].first;
    GenerateHeader(65, "Merge images screen");
    Image image2; string Image2name;
    cout << "\nPlease enter a new image to be merged with the current image\n>";
    EnterImageDataWithValidation(image2, Image2name);

    if (image.width == image2.width && image.height == image2.height) {
        MergeAlgo(image, image2);
        ShowEnd(65);
        return;
    }
    cout << '\n';
    vector<string> options = { "Resize images and merge",
    "Merge common area", "Back to menu" };
    int ChoiceNum = GenerateOptionsListAndChoose(options, 65);

    switch (ChoiceNum) {
    case 1:   ResizeMerge(image, image2);  break;
    case 2:  MergeCommonArea(image, image2); break;
    case 3:  MenuScreenAndOperatAFilter(vCurrentPicAndItsName); break;
    default: UnValidNumberMessage(1, 3); MergeImages(vCurrentPicAndItsName);
    }
}

// ===================++ Save & Load Filters ++=====================-

void EnterImageDataWithValidation(Image& image, string &filename) {

    if (cin.peek() == '\n') 
        cin.ignore();

    bool success = false;
    while (!success)
    {
        getline(cin, filename);

        if (IsExtensionFalse(filename)) {
            cout << "\a";
            cout << "\nError )-:, Please enter a valid extension [.jpg, .bmp, .png, .tga]\n>";
            continue;
        }

        try {
            image.loadNewImage(filename);
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
    if (!vCurrentPicAndItsName.empty()) {
        vector<string> options = { "Replace the old image with the modified one",
           "Save with different name and keep the old version", "Back to main menu" };
        int ChoiceNum = GenerateOptionsListAndChoose(options, 65);

        switch (ChoiceNum) {
        case 1: {
            vCurrentPicAndItsName[0].first.saveImage(vCurrentPicAndItsName[0].second);// == image.saveImage(selected_image);
            vAppliedFilters.clear();
            while (!stFiltersHistory.empty()) {
                stFiltersHistory.pop();
            }
            ShowEnd(65);
            break;
        }
        case 2: {
            cout << "\nPlease enter a new name for the edited image.\n";
            cout << "and specify extension [.jpg, .bmp, .png, .tga]: \n>";

            ////
            string OriginalImage = vCurrentPicAndItsName[0].second;
            ////

            cin.ignore();
            getline(cin, vCurrentPicAndItsName[0].second);
            while (IsExtensionFalse(vCurrentPicAndItsName[0].second)) {
                cout << "\a\nError )-:, Please enter a valid extension [.jpg, .bmp, .png, .tga]\n>";
                getline(cin, vCurrentPicAndItsName[0].second);
            }

            // Then save it with the same object and the new name he enterd
            vCurrentPicAndItsName[0].first.saveImage(vCurrentPicAndItsName[0].second);// == image.saveImage(selected_image);

            ////
            vCurrentPicAndItsName[0].second = OriginalImage;
            ////


            ShowEnd(65); break;
        }
        case 3: MenuScreenAndOperatAFilter(vCurrentPicAndItsName); break;

        default: UnValidNumberMessage(1, 3); SaveAnImage(vCurrentPicAndItsName); ////
        }
    }
    else {
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

    pair<Image, string> PCurrentPicAndItsName; // first == image // second == filename
    //fill The pair by this function -> EnterTheImageName(), and push it in vector
    EnterImageDataWithValidation(PCurrentPicAndItsName.first, PCurrentPicAndItsName.second);
    vCurrentPicAndItsName.push_back(PCurrentPicAndItsName);

    vAppliedFilters.clear();
    while (!stFiltersHistory.empty()) {
        stFiltersHistory.pop();
    }
    //
    ShowEnd(65);
}

// ===================++ Filters history ++=====================

void ClearImage(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    vAppliedFilters.clear();
    while (!stFiltersHistory.empty()) { stFiltersHistory.pop(); }

    Image image;
    image.loadNewImage(vCurrentPicAndItsName[0].second);
    vCurrentPicAndItsName[0].first = image;

    ShowEnd(65);
}

void Undo(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    stFiltersHistory.pop();

    if (!stFiltersHistory.empty()) vCurrentPicAndItsName[0].first = stFiltersHistory.top();
    else vCurrentPicAndItsName[0].first.loadNewImage(vCurrentPicAndItsName[0].second); // == image.loadNewImage(selected_image);

    vAppliedFilters.pop_back();

    if (!stFiltersHistory.empty()) { ShowEndInAppliedScreen(65); FiltersHistory(vCurrentPicAndItsName); }
    else ShowEnd(65);
}

void FiltersHistory(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    int Choice = AppliedFiltersScreen(65, vCurrentPicAndItsName);
    if (!Choice) return;
    switch (Choice) {
    case 1: ClearImage(vCurrentPicAndItsName); break;
    case 2: Undo(vCurrentPicAndItsName); break;
    case 3: MenuScreenAndOperatAFilter(vCurrentPicAndItsName);   break;
    default: UnValidNumberMessage(1, 3); FiltersHistory(vCurrentPicAndItsName);
    }
}

// ===================++ Menu screen functions ++=====================

void Exit(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    ClearScreen();
    char confirmation;
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

    GenerateHeader(65, "Main menu screen");
    vector<string> options = { "Load new image", "Grayscale filter","Black and white filter",
        "Invert image colors filter", "Flip image filter", "Brightness filter",
        "Rotate image filter", "Crop image", "Resize image", "Merge Images screen",
        "Save current image", "Show applied filters", "Exit" };
    
    int ChoiceNum = GenerateOptionsListAndChoose(options, 65);

    switch (ChoiceNum) {
    case enfilters::enLoadImage: LoadAnImage(vCurrentPicAndItsName); break;
    case enfilters::enGrayScale: Grayscale(vCurrentPicAndItsName); break;
    case enfilters::enBlackAndWhite: BlackAndWhite(vCurrentPicAndItsName); break;
    case enfilters::enInvertImage: InvertImage(vCurrentPicAndItsName); break;
    case enfilters::enFlipImage: FlipImage(vCurrentPicAndItsName); break;
    case enfilters::enDarkenAndLighten: DarkenAndLighten(vCurrentPicAndItsName); break;
    case enfilters::enRotateImage: RotateImage(vCurrentPicAndItsName); break;
    case enfilters::enCropImage: CropImage(vCurrentPicAndItsName); break;
    case enfilters::enResize: ResizeScreen(vCurrentPicAndItsName); break;
    case enfilters::enMerge: MergeImages(vCurrentPicAndItsName); break;
    case enfilters::enSaveImage: SaveAnImage(vCurrentPicAndItsName); break;
    case enfilters::enAppliedFiltersScreen: FiltersHistory(vCurrentPicAndItsName);  break;
    case enfilters::enExit: return 13;
    default: UnValidNumberMessage(1, 13);
        MenuScreenAndOperatAFilter(vCurrentPicAndItsName);
    } 
    return ChoiceNum;
}

void StartFilterProgram(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    int Choice;
    ClearScreen();

    do { Choice = MenuScreenAndOperatAFilter(vCurrentPicAndItsName); } while (Choice != 13);

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