<?php

namespace Database\Factories;

use Illuminate\Database\Eloquent\Factories\Factory;
use Illuminate\Support\Str;

class WorkoutFactory extends Factory
{
    public function definition()
    {
        $min = strtotime(date('2020-01-01'));
        $max = strtotime(date('Y-m-d'));
        $val = rand($min, $max);
        return [
            'date' => date('Y-m-d', $val),
            'duration' => rand(0, 7200),
            'calories' => rand(0, 1000),
            'max_puls' => rand(100, 180),
            'avg_puls' => rand(80, 150),
        ];
    }
}
