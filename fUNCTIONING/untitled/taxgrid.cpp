#include "taxgrid.h"

// Constructor for TaxGrid, no Qt dependencies, using PointF
TaxGrid::TaxGrid(PointF topLeft, PointF topRight, PointF bottomLeft, PointF bottomRight, const std::string& name, int taxAmount)
        : SpecialGrid(topLeft, topRight, bottomLeft, bottomRight, name), m_taxAmount(taxAmount) { }

// Getter for the tax amount
int TaxGrid::getTaxAmount() const {
    return m_taxAmount;
}
