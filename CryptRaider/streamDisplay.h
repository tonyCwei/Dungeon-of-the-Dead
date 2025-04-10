// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Styling/SlateColor.h"


#include "streamDisplay.generated.h"


/**
 * 
 */
class UTextBlock;

UCLASS()
class CRYPTRAIDER_API UstreamDisplay : public UUserWidget
{
	GENERATED_BODY()

public:
	//native construct needed
	virtual void NativeConstruct() override;

  

	void InitlizeCommentSection();

    
/*Comment Seciont*/

private:
    TArray<FString> userNameArr = {
        "KillaSoulful", "PilotDeity", "KickStart", "SniperSpirit", "CherryTiger",
        "CommanderZero", "StarViolence", "CobraSting", "SniperSuspicion", "BlitzGlory",
        "FurFoxie1559", "GrabbyPaws", "ProudHowl69", "ArrowTitan786", "PrankScamp",
        "HastyHippo", "RogueMaster", "HolyTrinity", "QuickAgile46", "ManeMenace42",
        "EyeRiot69", "PirateHacker", "HostileSurge17", "ClawRaid20", "LunarTitan45",
        "MadAxe1993", "EdgyFlame56", "EasySiren486", "FoeDefeat", "CheeseSiren",
        "GlowNova78", "FearDragon28", "FrenziedPunch", "RavenImpuls3", "EpicFusion333",
        "RobotBuilder", "PoppyNectar", "PinkPup348", "JubilantBud", "ValiantHen18",
        "RuggedSmasher", "SoldierHive", "DangerRaven", "WetBloom78", "RuggedGunner",
        "SharkLily777"
    };




    TArray<FSlateColor> userNameColor = {
        FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f)), // White
        FSlateColor(FLinearColor(252.0f / 255.0f, 207.0f / 255.0f, 3.0f / 255.0f, 1.0f)), // Yellow
        FSlateColor(FLinearColor(252.0f / 255.0f, 53.0f / 255.0f, 3.0f / 255.0f, 1.0f)), // Red
        FSlateColor(FLinearColor(3.0f / 255.0f, 152.0f / 255.0f, 252.0f / 255.0f, 1.0f)), // Blue
        FSlateColor(FLinearColor(3.0f / 255.0f, 252.0f / 255.0f, 90.0f / 255.0f, 1.0f)), // Green
        FSlateColor(FLinearColor(255.0f / 255.0f, 192.0f / 255.0f, 203.0f / 255.0f, 1.0f)), // Pink
        FSlateColor(FLinearColor(165.0f / 255.0f, 42.0f / 255.0f, 42.0f / 255.0f, 1.0f)), // Brown
        FSlateColor(FLinearColor(148.0f / 255.0f, 3.0f / 255.0f, 252.0f / 255.0f, 1.0f)) // Purple
    };

	
    TArray<FString> commentPool 
      /*  = {
        "Sup",
        "Suuuuuuup",
        "Whassup fam",
        "What's everyone up to?",
        "Who's hyped for today's stream?",
        "Finally! You haven't streamed for days!",
        "Just joined in, what did I miss?",
        "Hey everyone! Glad to be here for another stream",
        "Excited to see what's in store today!",
        "First time catching the stream live, super hyped!",
        "Been looking forward to this all day!",
        "Hope everyone's having a great day or night!",
        "Ready to kick back and enjoy the stream!",
        "What we doing today?",
        "Let's hope it's not boring as last time",
        "Good to see the stream live again!",
        "Missed the last stream, glad to be here today"
    }*/
    
    ;





    
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* userName0;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* comment0;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* userName1;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* comment1;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* userName2;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* comment2;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* userName3;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* comment3;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* userName4;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* comment4;

    TArray<UTextBlock*> userText;

    TArray<UTextBlock*> commentText;

    TArray<int32> colorIndices;

    int32 commentCount = 0;

    int32 maxComment;

    float commentFreq = 1.5;

    FTimerHandle commentTimeHandle;
    


public:
    UFUNCTION(BlueprintCallable)
    void nextComment();

    UFUNCTION(BlueprintCallable)
    void updateComment();

    UFUNCTION(BlueprintCallable)
    void clearComment() { commentPool.Empty(); }

    UFUNCTION(BlueprintCallable)
    int32 getCommentCount() const { return commentCount; }

    UFUNCTION(BlueprintCallable)
    void resetCommentCount() { commentCount = 0; }

    UFUNCTION(BlueprintCallable)
    void setMaxComment(int32 max) { maxComment = max; }

    UFUNCTION(BlueprintCallable)
    int32 getMaxComment() const { return maxComment; }

    UFUNCTION(BlueprintCallable)
    void setCommentFreq(float newFreq) { commentFreq = newFreq; }

    UFUNCTION(BlueprintCallable)
    float getCommentFreq() const { return commentFreq; }

    UFUNCTION(BlueprintCallable)
    void switchToGrabInstruction();

    UFUNCTION(BlueprintCallable)
    void switchToLockedExit();

    UFUNCTION(BlueprintCallable)
    void switchToLockedKeyOutStand();

    UFUNCTION(BlueprintCallable)
    void switchToCryptDoor();

    UFUNCTION(BlueprintCallable)
    void switchToCoffinChat();

    UFUNCTION(BlueprintCallable)
    void switchToSkeletonChat();

    UFUNCTION(BlueprintCallable)
    void switchToLevelExitChat();


    //Convai
    UFUNCTION(BlueprintCallable)
    void pushToCommentPool(FString comment);


//Viewer Section
    private:
        int32 curViewerCount = 500;

        int32 minViewerIncrease = -3;

        int32 maxViewerIncrease = 10;

        UPROPERTY(EditAnywhere)
        float viewerCountFreq = 5;

        UPROPERTY(meta = (BindWidget))
        UTextBlock* ViewerNumber;

        void nextViewerCount();

        FTimerHandle viewerTimeHandle;

        FTimerHandle resetTimer;

    public:



        UFUNCTION(BlueprintCallable)
        void updateViewerCount();

        UFUNCTION(BlueprintCallable)
        int32 getMinViewerIncrease() const { return minViewerIncrease; }

        UFUNCTION(BlueprintCallable)
        void setMinViewerIncrease(int32 newMinIncrease) { minViewerIncrease = newMinIncrease; }

        UFUNCTION(BlueprintCallable)
        void setMaxViewerIncrease(int32 newMaxIncrease) { maxViewerIncrease = newMaxIncrease; }

        UFUNCTION(BlueprintCallable)
        void setViewerCountFreq(float newFreq) { viewerCountFreq = newFreq;  }

        UFUNCTION(BlueprintCallable)
        void increaseViewer(int32 value, float increaseTime);

        UFUNCTION(BlueprintCallable)
        void resetViewerIncreaseStatus();

        
        UFUNCTION(BlueprintCallable)
        void clearTimeHandler();



};
