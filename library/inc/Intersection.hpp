namespace implicit
{
	class Intersection : public AbsOperation
	{
	public:
		Intersection(ImplicitGeometryPtr operand1, ImplicitGeometryPtr operand2);
		bool inside(double x, double y) const;
	};
}