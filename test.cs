namespace Data
{
	class Component
	{
		// Properties
		public int X { get; set; }
		public int Y { get; set; }
		public int Width { get; set; }
		public int Height { get; set; }
		public int Thickness { get; set; }

		// Constructor
		public Component(int x, int y, int width, int height, int thickness)
		{
			X = x;
			Y = y;
			Width = width;
			Height = height;
			Thickness = thickness;
		}
	}

	class ComputingData
	{
		// Properties
		public Component ExternalLayer { get; set; }
		public Component InternalLayer { get; set; }
		public Component InsulatedLayer { get; set; }
		public Component Hole { get; set; }

		// Constructor
		public ComputingData(Component externalLayer, Component internalLayer, Component insulatedLayer, Component hole)
		{
			ExternalLayer = externalLayer;
			InternalLayer = internalLayer;
			InsulatedLayer = insulatedLayer;
			Hole = hole;
		}
	}
}

namespace Computing
{
    class ComputingUtility
    {
        // Method to validate the data
        public static bool IsValid(Data.ComputingData data)
        {
            // Example validation logic
            if (data.ExternalLayer.Width <= 0 || data.ExternalLayer.Height <= 0 ||
                data.InternalLayer.Width <= 0 || data.InternalLayer.Height <= 0 ||
                data.InsulatedLayer.Width <= 0 || data.InsulatedLayer.Height <= 0 ||
                data.Hole.Width <= 0 || data.Hole.Height <= 0)
            {
                return false;
            }

            // If all checks pass, return true
            return true;
        }
    }
}

class Program
{
	static void Main(string[] args)
	{
		Component externalLayer = new Component(0, 0, 100, 200, 10);
        Component internalLayer = new Component(0, 0, 90, 190, 8);
        Component insulatedLayer = new Component(0, 0, 85, 180, 6);
        Component hole = new Component(10, 10, 20, 20, 2); // computed using the above layer's dimensions

		ComputingData computingData = new ComputingData(externalLayer, internalLayer, insulatedLayer, hole);

		bool isValid = ComputingUtility.IsValid(computingData);

		if (isValid)
		{
			// start computing
		}
		else
		{
			// return error
		}
	}
}
