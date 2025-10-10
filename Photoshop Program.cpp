/****************************************************
* Course: CS213
* Assignment : A1 - Part 1
*
*Section : 23-24
*
*Team Members :
* 1. Mohamed Jamal Mohamed - ID : 20242274
* 2. Ahmed Osama Sediq - ID : 20242004
* 3. Mazen Magdy Fouad - ID : 20240449
*
*Description :
*
*-Mohamed Jamal implemented :
*   *InvertImage
*   *RotateImage
*   *Add Frame
*   *blur
*   *Old TV
*
*-Ahmed Osama implemented :
*   *FlipImage
*   *BlackAndWhite
*   *Crop Image
*   *Resize Image
*   *Purple filter
*
*
*-Mazen Magdy implemented :
*   *GrayScale
*   *DarkenAndLighten
*   *DetectEdges
*   *Merging images
*   *Sunlight
*
*-The Menu was implemented by :
*   *Ahmed Osama
*   *Mohamed Jamal
*   *Mazen Magdy
*
****************************************************/
#include <iostream>
#include <algorithm>
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
    enDetectFilter = 11, enBlur = 12, enWanoSunlight = 13, enFrame = 14, enPurple = 15, enOldTV = 16,
    enSaveImage = 17, enAppliedFiltersScreen = 18, enExit = 19
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
    Image& image = vCurrentPicAndItsName[0].first;
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
    ShowEnd(60);
}

// ==================++ BlackAndWhite Filter ++=====================

void BlackAndWhite(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    GenerateHeader(65, "Black and White filter screen");
    Image& image = vCurrentPicAndItsName[0].first;
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

    Image& image = vCurrentPicAndItsName[0].first;
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
    ShowEnd(65);
}

//=================== ++Crop Filter++ =====================

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
            TempI = max(0.0f, TempI); TempI = min(oldWidth - 1, (int)TempI);
            Tempj = max(0.0f, Tempj); Tempj = min(oldHeight - 1, (int)Tempj);
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

void RatioAlgoAndinterface(Image& image) {

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
    int width = max(1, (int)round(image.width + image.width * ratio));
    int height = max(1, (int)round(image.height + image.height * ratio));

    ResizeAlgo(image, width, height);

}

void Resize(vector<pair<Image, string>>& vCurrentPicAndItsName) {


    Image& image = vCurrentPicAndItsName[0].first;
    GenerateHeader(65, "Resize image screen");
    vector<string> options = { "enter new dimensions" , "enter a ratio of reduction or increase" , "Back to menu" };

    int ChoiceNum = GenerateOptionsListAndChoose(options, 65); bool ReturnedToMenu = false;

    switch (ChoiceNum) {
    case 1:
    {
        GenerateHeader(65, "New dimensions entry screen");
        int width, height; cout << "\nPlease enter  (New width )\n>";
        cin >> width;
        cout << "Please enter  (New height )\n>";
        cin >> height;

        ResizeAlgo(image, width, height); break;
    }
    case 2:  RatioAlgoAndinterface(image); break;
    case 3:  MenuScreenAndOperatAFilter(vCurrentPicAndItsName); ReturnedToMenu = true;  break;
    default: UnValidNumberMessage(1, 3); Resize(vCurrentPicAndItsName);
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

// ===================++ Detect Image Edges Filters ++=====================-

void gray(Image& im) {
    for (int i = 0; i < im.width; i++) {
        for (int j = 0; j < im.height; j++) {
            int avg = 0;
            for (int k = 0; k < 3; k++) {
                avg += im(i, j, k);
            }
            avg /= 3;
            for (int k = 0; k < 3; k++) {
                im.setPixel(i, j, k, avg);
            }
        }
    }
}

void DetectFilter(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    GenerateHeader(65, "Detect Image Edges screen");
    Image& im = vCurrentPicAndItsName[0].first;
    gray(im);
    int kernelx[3][3] = { {1, 0, -1},
                         {2, 0, -2},
                         {1, 0, -1} };
    int kernely[3][3] = { {1, 2, 1},
                         {0, 0, 0},
                         {-1, -2, -1} };
    Image result(im.width, im.height);
    double totalmag = 0.0;
    int count = 0;
    for (int i = 0; i < im.width - 2; i++) {
        for (int j = 0; j < im.height - 2; j++) {
            int sumx = 0;
            int sumy = 0;
            for (int I = 0; I <= 2; I++) {
                for (int J = 0; J <= 2; J++) {
                    int pix = im(i + I, j + J, 0);
                    sumx += pix * kernelx[I][J];
                    sumy += pix * kernely[I][J];
                }
            }
            double mag = sqrt(sumx * sumx + sumy * sumy);
            int final_mag = min(255, max(0, (int)round(mag)));
            totalmag += final_mag;
            count++;
            for (int k = 0; k < 3; k++) {
                result.setPixel(i, j, k, final_mag);
            }
        }
    }
    double avg_mag = totalmag / count;
    for (int i = 0; i < im.width; i++) {
        for (int j = 0; j < im.height; j++) {
            int pix = result(i, j, 0);
            int val = (pix > avg_mag) ? 0 : 255;
            for (int k = 0; k < 3; k++) {
                result.setPixel(i, j, k, val);
            }
        }
    }
    im = result;
    stFiltersHistory.push(result);
    vAppliedFilters.push_back("Detect Edges filter");
    ShowEnd(65);
}

// ===================++ Blur Filter ++=====================-

void Blur(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    Image& image = vCurrentPicAndItsName[0].first;
    GenerateHeader(65, "Blur filter screen");
    int r;
    cout << "\nEnter blur radius: ";
    cin >> r;
    Image temp(image.width, image.height);
    vector<vector<vector<int>>> arr(
        image.width,
        vector<vector<int>>(image.height, vector<int>(3, 0))
    );

    arr[0][0][0] = image(0, 0, 0);
    arr[0][0][1] = image(0, 0, 1);
    arr[0][0][2] = image(0, 0, 2);


    for (int i = 1; i < image.width; i++) {
        for (int k = 0; k < 3; k++) {
            arr[i][0][k] = arr[i - 1][0][k];
        }
    }
    for (int i = 1; i < image.height; i++) {
        for (int k = 0; k < 3; k++) {
            arr[0][i][k] = arr[0][i - 1][k];
        }
    }
    for (int j = 1; j < image.height; j++) {
        for (int i = 1; i < image.width; i++) {
            for (int k = 0; k < 3; k++) {
                arr[i][j][k] = arr[i - 1][j][k] + arr[i][j - 1][k] + image(i, j, k) - arr[i - 1][j - 1][k];
            }
        }
    }

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int x1 = max(0, i - r);
            int y1 = max(0, j - r);
            int x2 = min(image.width - 1, i + r);
            int y2 = min(image.height - 1, j + r);

            for (int k = 0; k < 3; k++) {
                long long sum = arr[x2][y2][k]
                    - (x1 ? arr[x1 - 1][y2][k] : 0)
                    - (y1 ? arr[x2][y1 - 1][k] : 0)
                    + (x1 && y1 ? arr[x1 - 1][y1 - 1][k] : 0);

                int count = (x2 - x1 + 1) * (y2 - y1 + 1);

                temp(i, j, k) = sum / count;
            }
        }
    }
    image = temp;
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Blur filter");
    ShowEnd(65);
}

// ===================++ Sunlight Filter ++=====================

void WanoSunlightFilter(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    GenerateHeader(65, "Wano Sunlight screen");
    Image& image = vCurrentPicAndItsName[0].first;
    const int Br_Boost = 13;
    const int R_boost = 25;
    const int Gboost = 15;

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            unsigned char r = image(i, j, 0);
            unsigned char g = image(i, j, 1);
            unsigned char b = image(i, j, 2);

            int newR = r + Br_Boost + R_boost;
            int newG = g + Br_Boost + Gboost;
            int newB = b + Br_Boost - 50;

            if (newR > 255) newR = 255;
            if (newG > 255) newG = 255;
            if (newB > 255) newB = 255;

            if (newB < 0) newB = 0;

            image(i, j, 0) = newR;
            image(i, j, 1) = newG;
            image(i, j, 2) = newB;
        }
    }
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Wanno sunlight filter");
    ShowEnd(65);
}

// ===================++ Frame Filter ++=====================

void DrawRec(Image& image, int xStart, int xEnd, int yStart, int yEnd, int r, int g, int b) {
    for (int i = xStart; i < xEnd; i++) {
        for (int j = yStart; j < yEnd; j++) {
            if (i >= 0 && i < image.width && j >= 0 && j < image.height) {
                image(i, j, 0) = r;
                image(i, j, 1) = g;
                image(i, j, 2) = b;
            }
        }
    }
}

void SimpleFrame(Image& image) {
    int borderSize = 15;
    int colorValue = 150;


    DrawRec(image, 0, image.width, 0, borderSize, 0, 0, colorValue);


    DrawRec(image, 0, image.width, image.height - borderSize, image.height, 0, 0, colorValue);


    DrawRec(image, 0, borderSize, 0, image.height, 0, 0, colorValue);


    DrawRec(image, image.width - borderSize, image.width, 0, image.height, 0, 0, colorValue);
}

void FancyFrame(Image& image) {
    int R = 0, G = 0, B = 255;
    int W = 255;
    int Width = image.width;
    int Height = image.height;


    DrawRec(image, 0, Width, 0, 10, R, G, B);
    DrawRec(image, 0, Width, 10, 15, W, W, W);


    DrawRec(image, 0, Width, Height - 15, Height - 10, W, W, W);
    DrawRec(image, 0, Width, Height - 10, Height, R, G, B);


    DrawRec(image, 0, 10, 0, Height, R, G, B);
    DrawRec(image, 10, 15, 10, Height - 10, W, W, W);
    DrawRec(image, 10, 15, 0, 10, R, G, B);
    DrawRec(image, 10, 15, Height - 10, Height, R, G, B);


    DrawRec(image, Width - 10, Width, 0, Height, R, G, B);
    DrawRec(image, Width - 15, Width - 10, 10, Height - 10, W, W, W);
    DrawRec(image, Width - 15, Width - 10, 0, 10, R, G, B);
    DrawRec(image, Width - 15, Width - 10, Height - 10, Height, R, G, B);


    DrawRec(image, 15, 80, 60, 65, W, W, W);
    DrawRec(image, 75, 80, 15, 60, W, W, W);
    DrawRec(image, 15, 35, 30, 35, W, W, W);
    DrawRec(image, 30, 35, 15, 30, W, W, W);


    DrawRec(image, Width - 80, Width - 15, 55, 60, W, W, W);
    DrawRec(image, Width - 80, Width - 75, 15, 60, W, W, W);
    DrawRec(image, Width - 35, Width - 15, 30, 35, W, W, W);
    DrawRec(image, Width - 35, Width - 30, 15, 30, W, W, W);


    DrawRec(image, 15, 80, Height - 60, Height - 55, W, W, W);
    DrawRec(image, 75, 80, Height - 60, Height - 15, W, W, W);
    DrawRec(image, 15, 35, Height - 35, Height - 30, W, W, W);
    DrawRec(image, 30, 35, Height - 30, Height - 15, W, W, W);


    DrawRec(image, Width - 80, Width - 15, Height - 60, Height - 55, W, W, W);
    DrawRec(image, Width - 80, Width - 75, Height - 60, Height - 15, W, W, W);
    DrawRec(image, Width - 35, Width - 15, Height - 35, Height - 30, W, W, W);
    DrawRec(image, Width - 35, Width - 30, Height - 30, Height - 15, W, W, W);
}

void AddFrameToImage(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    Image& image = vCurrentPicAndItsName[0].first;
    GenerateHeader(65, "Frame screen");
    vector<string> options = { "Simple frame", "Fancy frame", "Back to menu" };
    int ChoiceNum = GenerateOptionsListAndChoose(options, 65);
    bool ReturnedToMenu = false;
    switch (ChoiceNum) {
    case 1: SimpleFrame(image); break;
    case 2: FancyFrame(image); break;
    case 3: MenuScreenAndOperatAFilter(vCurrentPicAndItsName); ReturnedToMenu = true; break;
    default: UnValidNumberMessage(1, 3); AddFrameToImage(vCurrentPicAndItsName);
    }

    if (!ReturnedToMenu) {
        stFiltersHistory.push(image);
        vAppliedFilters.push_back("Added Frame");
        ShowEnd(65);
    }
}

// ===================++ Purple Filter ++=====================

void purpleFilter(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    GenerateHeader(65, "Purple filter screen");
    Image& image = vCurrentPicAndItsName[0].first;
    int Rboost = 35;
    int Bboost = 55;
    float Gboost = .9;
    float Factor = .9;

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            int r = image(i, j, 0);
            int g = image(i, j, 1);
            int b = image(i, j, 2);

            int newR = r + Rboost;
            int newG = (int)(g * Gboost);
            int newB = b + Bboost;

            newR = (int)(newR * Factor);
            newG = (int)(newG * Factor);
            newB = (int)(newB * Factor);

            if (newR > 255) newR = 255;
            if (newG > 255) newG = 255;
            if (newB > 255) newB = 255;

            if (newR < 0) newR = 0;
            if (newG < 0) newG = 0;
            if (newB < 0) newB = 0;

            image(i, j, 0) = newR;
            image(i, j, 1) = newG;
            image(i, j, 2) = newB;
        }
    }
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Purple filter");
    ShowEnd(65);
}

// ===================++ Old TV Filter ++=====================

void addNoise(Image& image) {
    int modNum = 30;
    for (int i = 0; i < image.height; ++i) {
        for (int j = 0; j < image.width; ++j) {
            for (int c = 0; c < image.channels; ++c) {
                int val = image(j, i, c);
                int noise = (rand() % (2 * modNum)) - modNum;
                val += noise;

                if (val < 0) val = 0;
                if (val > 255) val = 255;

                image(j, i, c) = (unsigned char)val;
            }
        }
    }
}


void addScanlines(Image& image) {
    for (int i = 0; i < image.height - 1; ++i) {
        if (i % 4 == 0) {
            for (int j = 0; j < image.width; ++j) {
                for (int c = 0; c < image.channels; ++c) {
                    int val = image(j, i, c);
                    val = val * .4;
                    image(j, i, c) = (unsigned char)val;
                    image(j, i + 1, c) = (unsigned char)val;
                }
            }
        }
    }
}

void applyColorDistortion(Image& image) {
    int modNum = 20;
    for (int i = 0; i < image.height; ++i) {
        for (int j = 0; j < image.width; ++j) {
            int randnum = rand() % 3 + 1;
            int distortion = (rand() % modNum) - modNum / 2;

            int val;
            int channel_index;

            if (randnum == 1) {
                val = image(j, i, 0);
                channel_index = 0;
            }
            else if (randnum == 2) {
                val = image(j, i, 1);
                channel_index = 1;
            }
            else {
                val = image(j, i, 2);
                channel_index = 2;
            }

            val += distortion;

            if (val > 255) val = 255;
            if (val < 0) val = 0;

            image(j, i, channel_index) = val;
        }
    }
}

void oldTVFilter(vector<pair<Image, string>>& vCurrentPicAndItsName) {
    GenerateHeader(65, "Old TV filter screen");
    Image& image = vCurrentPicAndItsName[0].first;
    addNoise(image);
    addScanlines(image);
    applyColorDistortion(image);
    stFiltersHistory.push(image);
    vAppliedFilters.push_back("Old TV filter");
    ShowEnd(65);
}

// ===================++ Save & Load Filters ++=====================

void EnterImageDataWithValidation(Image& image, string& filename) {

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
    if (!stFiltersHistory.empty()) {
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
        cout << "\nError :-(, apply a filter at first then save it after editing\n\n";
        cout << "\aPlease press any key to go back to main menu then apply a filter....\n>";
        system("pause>0");
    }
}


void LoadAnImage(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    GenerateHeader(65, "Load image screen");
    // we at first check if there are applied filters
    if (!stFiltersHistory.empty()) {
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
    // There are only two cases to be here (if he pressed 2 when there is a image) / (if there is no applied filters)
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
    if (!stFiltersHistory.empty()) {
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
    else {
        PuttyEndingMessage();
    }

}

int MenuScreenAndOperatAFilter(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    GenerateHeader(65, "Main menu screen");
    vector<string> options = { "Load new image", "Grayscale filter","Black and white filter",
        "Invert image colors filter", "Flip image filter", "Brightness filter",
        "Rotate image filter", "Crop image", "Resize image", "Merge Images screen",
        "Detect Image edges", "Blur Filter screen", "Wano sunlight filter", "Add frame", "Purple filter",
        "Old TV filter", "Save current image", "Show applied filters", "Exit" };

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
    case enfilters::enResize: Resize(vCurrentPicAndItsName); break;
    case enfilters::enMerge: MergeImages(vCurrentPicAndItsName); break;
    case enfilters::enDetectFilter:DetectFilter(vCurrentPicAndItsName); break;
    case enfilters::enBlur: Blur(vCurrentPicAndItsName); break;
    case enfilters::enWanoSunlight: WanoSunlightFilter(vCurrentPicAndItsName); break;
    case enfilters::enFrame: AddFrameToImage(vCurrentPicAndItsName); break;
    case enfilters::enPurple: purpleFilter(vCurrentPicAndItsName); break;
    case enfilters::enOldTV: oldTVFilter(vCurrentPicAndItsName); break;
    case enfilters::enSaveImage: SaveAnImage(vCurrentPicAndItsName); break;
    case enfilters::enAppliedFiltersScreen: FiltersHistory(vCurrentPicAndItsName);  break;
    case enfilters::enExit: return 19;
    default: UnValidNumberMessage(1, 19);
        MenuScreenAndOperatAFilter(vCurrentPicAndItsName);
    }
    return ChoiceNum;
}

void StartFilterProgram(vector<pair<Image, string>>& vCurrentPicAndItsName) {

    int Choice;
    ClearScreen();

    do { Choice = MenuScreenAndOperatAFilter(vCurrentPicAndItsName); } while (Choice != 19);

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