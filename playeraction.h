#ifndef PLAYERACTION_H
#define PLAYERACTION_H

enum class PlayerAction {
    NoAction,
    BuyProperty,
    CannotAffordProperty,
    BuildHouse,
    CannotBuildHouse,
    BuildHotel,
    CannotBuildHotel,
    PaidRent,
    CannotAffordRent,
    GoToJail,
    FreeParking,
    SurpriseCardAdvanceToGo,
    SurpriseCardDividend,
    SurpriseCardGoBack3Spaces,
    SurpriseCardGoToJail,
    SurpriseCardRepairs,
    SurpriseCardPayPoorTax,
    SurpriseCardTripToRailroad,
    SurpriseCardWalkOnBoardwalk,
    SurpriseCardElectedChairman,
    SurpriseCardBuildingLoanMatures,
    SurpriseCardGetOutOfJailFree,
    SurpriseCardAdvanceToIllinois,
    SurpriseCardAdvanceToStCharles,
    SurpriseCardStreetRepairs,
    SurpriseCardNearestUtility,
    SurpriseCardNearestRailroad,
    TaxPaid,
    JailTurn,
    OutOfJail,
    DeclareBankruptcyToBank,      // Declare bankruptcy to the bank
    DeclareBankruptcyToPlayer     // Declare bankruptcy to another player
};

#endif // PLAYERACTION_H
