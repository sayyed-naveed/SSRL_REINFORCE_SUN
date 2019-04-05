The dirs are named REINFORCE_SUN but they really represent both:
- REINFORCE SUN
- S*RL 
algorithm implementations

To run one or the other make the following changes, build code and set the input/output data dirs appropriately:

1)- Weight Update: In the method: SUNImmediateReinforceController::UpdateWeights, comment/uncomment the corresponding weight update equation. Both versions are commented appropriately and is quite straight forward

2)- Sigma Update: 
	In the methods: 
		- SynapseImmediateReinforceController::UpdateSigma
		- UnitImmediateReinforceController::UpdateSigma
		- NetworkImmediateReinforceController::UpdateSigma

	comment/uncomment the corresponding sigma update equation. Both versions are commented appropriately and is quite straight forward as well.


For any questions, please send email to sayyed.naveed@gmail.com