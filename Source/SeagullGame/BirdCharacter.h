

#pragma once

#include "GameFramework/Character.h"
#include "BirdCharacter.generated.h"

/**
 * 
 */
UCLASS(config = Game)
class ABirdCharacter : public ACharacter
{
public:
	GENERATED_UCLASS_BODY()

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		TSubobjectPtr<class USpringArmComponent> SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		TSubobjectPtr<class UCameraComponent> Camera;

	// Begin AActor overrides
	virtual void Tick(float DeltaSeconds) OVERRIDE;
	virtual void ReceiveHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) OVERRIDE;
	// End AActor overrides

	
	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// How fast the bird rotates
		float TurnSpeed;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// Upwards force when flapping
		float VertFlapStrength;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// Maximum velocity when travelling upwards
		float MaxVerticalFlapVelocity;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// Has the player unlocked the glide ability
		bool GlidingUnlocked;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// The downwards force placed on the player
		float FlyingGravityStrength;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// The max force when gliding - influenced by LatFlapForce and GlideDragAmount
		float MaxGlideForce;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// The drag imparted against LatFlapForce when gliding - also increases dive speed
		float GlideDragAmount;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// the max speed when flapping or gliding
		float GlideMaxSpeed;

	UPROPERTY(Category = Bird, EditAnywhere, BlueprintReadWrite)
		// The max speed when not flapping or gliding
		float FallingMaxSpeed;

	UPROPERTY(Category = Bird, BlueprintReadOnly)
		// Is the player currently gliding
		bool Gliding;

	UPROPERTY(Category = Bird, BlueprintReadOnly)
		// The force that flapping adds to forward/sideways movement
		float LatFlapForce;

protected:

	// Begin APawn overrides
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE; // Allows binding actions/axes to functions
	// End APawn overrides

	// Toggle forward movement
	void ThrustInput(float Val);

	// Event for Rotations
	void OnRightFlap(float Val);

	/// Rotates the bird around it's axis
	void RotateBird(float Val);

	// Called when the main flap button is pressed
	void Flap();

	// Function which stops gliding when glide button is released
	void StopGlide();

	// Strafes the player left or right when gliding
	void Strafe(float Val);

private:

	// Current yaw speed 
	float CurrentYawSpeed;

	// Current pitch speed
	float CurrentPitchSpeed;

	// Current roll speed 
	float CurrentRollSpeed;

	// Was the right wing just flapped
	bool RightFlapped;
	// Was the right wing just flapped
	bool LeftFlapped;
	// Were both wings just flapped
	bool ForwardPressed;

	/** Timers for wing flap spacing*/
	// Cooldown for right wing
	float RightTimer;
	// Cooldown for right wing
	float LeftTimer;
	// Cooldown for both wings
	float BothTimer;

	
};