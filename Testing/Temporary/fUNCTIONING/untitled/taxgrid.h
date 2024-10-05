#ifndef TAXGRID_H
#define TAXGRID_H

#include "specialgrid.h"
#include <string>

class TaxGrid : public SpecialGrid {
public:
    // Constructor taking standard C++ types
    TaxGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name, int taxAmount);
    int getTaxAmount() const;
private:
    int m_taxAmount;
};

#endif // TAXGRID_H
