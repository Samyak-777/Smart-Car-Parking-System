># Smart Car Parking System

# Contents
- [Overview](#overview)
-  [Features](#features)
- [Usage](#usage)
   - [Vehicle Entry](#vehicle-entry)
   - [Vehicle Exit](#vehicle-exit)
- [Allocation Policy](#allocation-policy)
- [Membership Policy](#membership-policy)
- [Payment Policy](#payment-policy)
- [Technologies Used](#technologies-used)
- [Conclusion](#conclusion)
  
## Overview
The Smart Car Parking System is an application designed to efficiently manage a parking lot with 50 parking spaces. The system tracks the occupancy status of each space, manages vehicle registrations, and applies membership benefits to enhance user experience. 

## Features
- **Parking Space Management**: Tracks 50 parking spaces, indicating whether each space is free (0) or occupied (1).
- **Vehicle Registration**: Records vehicle details including vehicle number, owner name, arrival/departure times, and membership status.
- **Dynamic Space Allocation**: Allocates parking spaces based on user membership (golden, premium, or no membership) following specific allocation policies.
- **Membership Benefits**: Updates user membership based on total parking hours and provides discounts on parking fees.
- **Payment Calculation**: Calculates parking fees based on duration with a structured payment policy.
- **Sorting Mechanisms**: Sorts vehicles based on the number of parkings done, amount paid, and sorts parking spaces by occupancy and revenue generated.

## Usage
1. **Vehicle Entry**:
   - When a vehicle enters, check for available parking spaces.
   - If it's the first entry, register the vehicle's details.
   - If already registered, update the arrival time and mark the space as occupied.

2. **Vehicle Exit**:
   - Calculate the number of hours parked and update total parking hours.
   - Update membership status if applicable.
   - Calculate payment due and change the space status to free.

3. **Sorting Options**:
   - Sort vehicles by the number of times parked or by total payment made.
   - Sort parking spaces based on occupancy frequency and revenue generation.

## Allocation Policy
- Golden members are allocated spaces 1-10.
- Premium members are allocated spaces 11-20.
- Non-members are allocated spaces beyond 20.

## Membership Policy
- Premium membership for users with 100+ total parking hours.
- Golden membership for users with 200+ total parking hours.

## Payment Policy
- ₹100 for the first 3 hours; ₹50 for each additional hour.
- 10% discount for members.

## Technologies Used
- C/C++ for application development
- Arrays of structures for data management
- Sorting algorithms for efficient data handling

## Conclusion
The Smart Car Parking System enhances parking efficiency through its automated management features and user-friendly interface. It offers a practical solution to modern urban parking challenges while providing benefits to users based on their membership status.

---
