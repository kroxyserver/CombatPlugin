# CombatPlugin
An Unreal Engine Plugin for integrating Combat Mechanics. (UE5.2.1)

# Add this to your DefaultEngine.ini

[/Script/Engine.CollisionProfile]

+Profiles=(Name="Projectile",CollisionEnabled=QueryAndPhysics,bCanModify=True,ObjectTypeName="Projectile",CustomResponses=((Channel="WorldStatic",Response=ECR_Overlap),(Channel="WorldDynamic",Response=ECR_Overlap),(Channel="Pawn",Response=ECR_Overlap),(Channel="Visibility",Response=ECR_Overlap),(Channel="Camera",Response=ECR_Overlap),(Channel="PhysicsBody",Response=ECR_Overlap),(Channel="Vehicle",Response=ECR_Overlap),(Channel="Destructible",Response=ECR_Overlap),(Channel="Projectile",Response=ECR_Overlap)),HelpMessage="Projectile")
+DefaultChannelResponses=(Channel=ECC_GameTraceChannel1,DefaultResponse=ECR_Overlap,bTraceType=False,bStaticObject=False,Name="Projectile")
+EditProfiles=(Name="Pawn",CustomResponses=((Channel="Projectile",Response=ECR_Overlap)))
+EditProfiles=(Name="CharacterMesh",CustomResponses=((Channel="Projectile",Response=ECR_Ignore)))
+EditProfiles=(Name="UI",CustomResponses=((Channel="Projectile",Response=ECR_Ignore)))