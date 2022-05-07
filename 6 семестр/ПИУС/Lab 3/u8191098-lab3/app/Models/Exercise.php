<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Exercise extends Model
{
    use HasFactory;

    /**
     * The attributes that are mass assignable.
     *
     * @var array<int, string>
     */
    protected $fillable = [
        'name',
        'exercise_type_id',
        'muscle_group_id',
    ];

    public function exerciseType()
    {
        return $this->belongsTo(ExerciseType::class, 'exercise_type_id', 'id');
    }

    public function muscleGroup()
    {
        return $this->belongsTo(MuscleGroup::class, 'muscle_group_id', 'id');
    }

    public function sets()
    {
        return $this->hasMany(Set::class);
    }
}
