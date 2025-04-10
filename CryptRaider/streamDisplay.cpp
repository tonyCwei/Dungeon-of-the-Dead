// Fill out your copyright notice in the Description page of Project Settings.


#include "streamDisplay.h"
#include "Components/TextBlock.h"
#include "Math/RandomStream.h"
#include "TimerManager.h"


void UstreamDisplay::NativeConstruct()
{
    Super::NativeConstruct();
    InitlizeCommentSection();
    updateViewerCount();
    
}




void UstreamDisplay::InitlizeCommentSection()
{
    userText = { userName0, userName1, userName2, userName3, userName4 };
    commentText = { comment0, comment1, comment2, comment3, comment4 };

    for (int i = 0; i < userText.Num(); ++i) {
        int32 colorIndex = FMath::RandRange(0, userNameColor.Num()-1);
        colorIndices.Push(colorIndex);
        userText[i]->SetText(FText::FromString(""));
        userText[i]->SetColorAndOpacity(userNameColor[colorIndex]);
        FString comment = "";
        commentText[i]->SetText(FText::FromString(comment));
    }

}

void UstreamDisplay::nextComment()
{
    for (int i = userText.Num() - 1; i > 0; --i) {
        userText[i]->SetText(userText[i-1]->GetText());


        colorIndices[i] = colorIndices[i - 1];
        userText[i]->SetColorAndOpacity(userNameColor[colorIndices[i]]);

        commentText[i]->SetText(commentText[i - 1]->GetText());
    }

    // User Name
    int32 UserNameIndex = FMath::RandRange(0, userNameArr.Num()-1);
    userText[0]->SetText(FText::FromString(userNameArr[UserNameIndex]));

    // Name Color
    int32 colorIndex = FMath::RandRange(0, userNameColor.Num()-1);
    colorIndices[0] = colorIndex;
    userText[0]->SetColorAndOpacity(userNameColor[colorIndex]);

    // User Comment
    int32 commentIndex = FMath::RandRange(0, commentPool.Num()-1);

    FString comment = ": " + commentPool[commentIndex];
    commentText[0]->SetText(FText::FromString(comment));
    commentPool.RemoveAtSwap(commentIndex);


    
}

void UstreamDisplay::updateComment()
{
    GetWorld()->GetTimerManager().SetTimer(commentTimeHandle, [&]()
        {   
            if (commentPool.IsEmpty() || commentCount >= maxComment) {
                GetWorld()->GetTimerManager().ClearTimer(commentTimeHandle);
                clearComment();
                return;
            }
            nextComment();
            commentCount++;
            
        }, commentFreq, true, 0);

}

void UstreamDisplay::switchToGrabInstruction() {
    resetCommentCount();
    setMaxComment(3);
    setCommentFreq(1.5);

    commentPool = {
        "Use your left mouse",
        "try LMB",
        "Dude, hold left click"
    };

    updateComment();
}

void UstreamDisplay::switchToLockedExit()
{
    resetCommentCount();
    setMaxComment(3);
    setCommentFreq(1.5);

    commentPool = {
        "This seems to be your exit",
        "It's locked",
        "You gotta find a way to open it"
    };

    updateComment();

}

void UstreamDisplay::switchToLockedKeyOutStand()
{

    resetCommentCount();
    setMaxComment(2);
    setCommentFreq(1.5);

    commentPool = {
        "This stand needs a statue",
        "This could be your key to get out!"
    };

    updateComment();
}

void UstreamDisplay::switchToCryptDoor()
{

    resetCommentCount();
    setMaxComment(8);
    setCommentFreq(1.25);
    viewerCountFreq = 0.01;

    commentPool = {
         "Yes!",
        "Deadly dungeon here we coooome",
        "Great job!",
        "Omg, what's down there",
        "This is going to be epic!",
        "Get ready for some action!",
        "Beware of the traps!",
        "Adventure time!",
        "Here comes the treasure!",
        "Time to face the unknown!",
        "This is intense!",
        "Watch out for the monsters!",
        "Can't wait to see what's next!",
        "Good luck down there!"
    };

    updateComment();
    increaseViewer(0, 4);
    GetWorld()->GetTimerManager().ClearTimer(viewerTimeHandle);
    updateViewerCount();
}

void UstreamDisplay::switchToCoffinChat()
{
    resetCommentCount();
    setMaxComment(5);
    setCommentFreq(1.25);
    viewerCountFreq = 0.01;

    commentPool = {
         "Go back out",
        "Check out the coffin outside",
        "Where did that crying go?",
        "omgomgomgomg",
        "Why is there a SKELETON here?"
    };


    updateComment();
    increaseViewer(0, 2);
    GetWorld()->GetTimerManager().ClearTimer(viewerTimeHandle);
    updateViewerCount();
    
}

void UstreamDisplay::switchToSkeletonChat()
{

    resetCommentCount();
    setMaxComment(5);
    setCommentFreq(1.25);
    viewerCountFreq = 0.01;

    commentPool = {
        "Whyyy, skeleton, whyyyy",
        "We are not gonna die here, chat!",
        "Holy, the jump scare is real",
        "Back off, skeleton",
        "WTFFFFFF"

    };

    updateComment();
    increaseViewer(2,4);
    GetWorld()->GetTimerManager().ClearTimer(viewerTimeHandle);
    updateViewerCount();
}


void UstreamDisplay::switchToLevelExitChat()
{

    resetCommentCount();
    setMaxComment(10);
    setCommentFreq(1.25);

    commentPool = {
        "Freedoooommm",
        "Finally!",
        "What a great stream, everyone!",
        "Good luck on your next adventure!",
        "Congrats!",
        "Amazing job today!",
        "What a journey, well done!",
        "This was so much fun!",
        "Can't wait to see what's next!",
        "You did it!"
    };

    updateComment();
    
}


void UstreamDisplay::pushToCommentPool(FString comment)
{
    commentPool.Push(comment);
}


void UstreamDisplay::nextViewerCount()
{
   
    int32 viewerCount = curViewerCount + FMath::RandRange(minViewerIncrease, maxViewerIncrease);
    curViewerCount = viewerCount;
    
    TArray<FString> viewerCountDigits;
    while (viewerCount > 0) {
        FString digit = FString::FromInt(viewerCount % 10);
        viewerCountDigits.Push(digit);
        viewerCount /= 10;
    }

    FString viewerCountString;
    int32 count = 0;
    for (FString digit : viewerCountDigits) {

        if (count == 3) {
            viewerCountString = "," + viewerCountString;
            count = 0;
        }

        viewerCountString = digit + viewerCountString;
        count++;
    }
    
    if (ViewerNumber) {
        ViewerNumber->SetText(FText::FromString(viewerCountString));
    }
   
}

void UstreamDisplay::updateViewerCount()
{
    GetWorld()->GetTimerManager().SetTimer(viewerTimeHandle, [&]()
        {
            nextViewerCount();

        }, viewerCountFreq, true, 0);

}



void UstreamDisplay::increaseViewer(int32 value, float increaseTime)
{
    minViewerIncrease += value;
    maxViewerIncrease += value;

    GetWorld()->GetTimerManager().SetTimer(resetTimer, [&]()
        {
            resetViewerIncreaseStatus();
            updateViewerCount();

        }, increaseTime, false
    );
}

void UstreamDisplay::resetViewerIncreaseStatus()
{
    minViewerIncrease = -3;
    maxViewerIncrease = 10;
    viewerCountFreq = 4;
}

void UstreamDisplay::clearTimeHandler()
{
    GetWorld()->GetTimerManager().ClearTimer(commentTimeHandle);
    GetWorld()->GetTimerManager().ClearTimer(viewerTimeHandle);
    GetWorld()->GetTimerManager().ClearTimer(resetTimer);
}


